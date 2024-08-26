// Copyright (c) 2024 Devexperts LLC.
// SPDX-License-Identifier: MPL-2.0

#include <plugin-api.h>

#include <dxfeed_graal_cpp_api/api.hpp>

#include <memory>

using namespace dxfcpp;

class Plugin final {
    std::shared_ptr<DXEndpoint> endpoint;
    std::shared_ptr<DXFeedSubscription> subscription;

    Plugin() noexcept {
        try {
            endpoint = DXEndpoint::create();
            subscription = endpoint->getFeed()->createSubscription(
                {Quote::TYPE, Trade::TYPE});
        } catch (const RuntimeException &e) {
            std::cerr << e << '\n';
        }
    }

public:
    ~Plugin() noexcept = default;

    std::shared_ptr<DXEndpoint> getEndpoint() const noexcept {
        return endpoint;
    }

    std::shared_ptr<DXFeedSubscription> getSubscription() const noexcept {
        return subscription;
    }

    static Plugin &getInstance() noexcept {
        static Plugin instance{};

        return instance;
    }
};

extern "C" {

DLLSAMPLE_API void dsp_init() {

}

DLLSAMPLE_API void dsp_connect(const char *address) {
    try {
        Plugin::getInstance().getEndpoint()->connect(address);
    } catch (const RuntimeException &e) {
        std::cerr << e << '\n';
    }
}

DLLSAMPLE_API void dsp_subscribe(const char *symbol, dsp_events_listener events_listener, void *user_data) {
    Plugin::getInstance().getSubscription()->addEventListener([user_data, events_listener](const auto &events) {
        auto size = events.size();

        if (size == 0) {
            return;
        }

        auto *eventsToListener = new dsp_event_t *[size];

        std::size_t index = 0;

        for (const auto &e : events) {
            if (const auto &q = e->template sharedAs<Quote>(); q) {
                eventsToListener[index++] = dxfcpp::bit_cast<dsp_event_t *>(
                    new dsp_quote_t{{DSP_ET_QUOTE}, q->getBidPrice(), q->getBidSize(), q->getAskPrice(),
                                    q->getAskSize()});
            } else if (const auto &tr = e->template sharedAs<Trade>(); tr) {
                eventsToListener[index++] = dxfcpp::bit_cast<dsp_event_t *>(
                    new dsp_trade_t{{DSP_ET_TRADE}, tr->getPrice(), tr->getSize()});
            }
        };

        events_listener(eventsToListener, index, user_data);

        for (std::size_t i = 0; i < index; i++) {
            if (eventsToListener[i]->type == DSP_ET_QUOTE) {
                delete dxfcpp::bit_cast<dsp_quote_t *>(eventsToListener[i]);
            } else if (eventsToListener[i]->type == DSP_ET_TRADE) {
                delete dxfcpp::bit_cast<dsp_trade_t *>(eventsToListener[i]);
            }
        }

        delete[] eventsToListener;
    });

    Plugin::getInstance().getSubscription()->addSymbols(symbol);
}

DLLSAMPLE_API void dsp_deinit() {

}

}