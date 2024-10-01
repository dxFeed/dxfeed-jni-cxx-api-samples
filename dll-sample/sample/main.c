// Copyright (c) 2024 Devexperts LLC.
// SPDX-License-Identifier: MPL-2.0

#include <plugin-api.h>

#define UNICODE
#define WIN32_LEAN_AND_MEAN

#include "Windows.h"
#include <stdio.h>

void listener(dsp_event_t **events, size_t size, void *user_data) {
    if (size == 0 || events == NULL) {
        return;
    }

    char *symbol = user_data == NULL ? "" : (char *)(user_data);

    for (size_t i = 0; i < size; i++) {
        if (events[i]->type == DSP_ET_QUOTE) {
            dsp_quote_t *q = (dsp_quote_t *)(events[i]);

            printf("Quote{%s, bid_price = %.15g, bid_size = %.15g, ask_price = %.15g, ask_size = %.15g}\n", symbol,
                   q->bid_price, q->bid_size, q->ask_price, q->ask_size);
        } else if (events[i]->type == DSP_ET_TRADE) {
            dsp_trade_t *tr = (dsp_trade_t *)(events[i]);

            printf("Trade{%s, price = %.15g, size = %.15g, dayVolume = %.15g}\n", symbol, tr->price, tr->size,
                   tr->dayVolume);
        }
    }
}

int main(int argc, char **argv) {
    if (argc == 2 && (strcmp("-?", argv[1]) == 0 || strcmp("-h", argv[1]) == 0)) {
        printf("Usage: %s <address> <symbol>\n"
               "Where:\n\n"
               "<address> - data source address (demo.dxfeed.com:7300 etc),\n"
               "            demo.dxfeed.com:7300 - default\n"
               "<symbol>  - security symbol (e.g. IBM, AAPL, SPX etc.), AAPL - default\n\n"
               "Example: dllsample-sample demo.dxfeed.com:7300 AAPL\n\n",
               argv[0]);

        return 0;
    }

    HMODULE plugin_handle = LoadLibrary(L"dllsample-dxfeed-plugin.dll");

    if (plugin_handle == NULL) {
        return 42;
    }

    dsp_init_fn_t dsp_init = (dsp_init_fn_t)(GetProcAddress(plugin_handle, "dsp_init"));
    dsp_connect_fn_t dsp_connect = (dsp_connect_fn_t)(GetProcAddress(plugin_handle, "dsp_connect"));
    dsp_subscribe_fn_t dsp_subscribe = (dsp_subscribe_fn_t)(GetProcAddress(plugin_handle, "dsp_subscribe"));
    dsp_deinit_fn_t dsp_deinit = (dsp_deinit_fn_t)(GetProcAddress(plugin_handle, "dsp_deinit"));

    if (dsp_init == NULL || dsp_connect == NULL || dsp_subscribe == NULL || dsp_deinit == NULL) {
        FreeLibrary(plugin_handle);

        return 5;
    }

    char *address = "demo.dxfeed.com:7300";
    char *symbol = "AAPL";

    if (argc > 1) {
        address = argv[1];
    }

    if (argc > 2) {
        symbol = argv[2];
    }

    printf("Connecting to %s\n", address);
    dsp_connect(address);
    printf("Subscribing to %s\n", symbol);
    dsp_subscribe(symbol, listener, symbol);

    Sleep(10000);
    FreeLibrary(plugin_handle);

    return 0;
}
