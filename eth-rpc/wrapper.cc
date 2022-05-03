#pragma once

#include "wrapper.hh"
#include <curl/curl.h>
#include <iostream>
#include <memory>
#include <string.h>

Wrapper::Wrapper(char *uri)
{
    rpc = uri;
}

Getter Wrapper::Getter()
{
    return Getter();
}

Sender Wrapper::Sender()
{
    return Sender();
}

size_t Wrapper::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr)
    {
        printf("Could not allocate memory to the uri variable.\n");
        fflush(stdout);
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void Wrapper::SendJson(char *endpt, Json::Value *buffer)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        struct MemoryStruct chunk;
        chunk.memory = (char *)malloc(1);
        chunk.size = 0;

        char *uri = (char *)malloc((strlen(rpc) + strlen(endpt) + 1) * sizeof(char));
        strcpy(uri, rpc);
        strcat(uri, endpt);

        curl_easy_setopt(curl, CURLOPT_URL, uri);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Wrapper::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK)
        {
            JSONCPP_STRING err;

            Json::CharReaderBuilder builder;
            const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
            if (!reader->parse(chunk.memory, chunk.memory + chunk.size, buffer, &err))
            {
                std::cout << "eth-rpc: Failed to parse JSON response." << std::endl;
            }
        }
        else
        {
            std::cout << "eth-rpc: Request failed." << std::endl;
        }

        free(uri);

        free(chunk.memory);
        curl_easy_cleanup(curl);
    }
    else
    {
        std::cout << "eth-rpc: Failed to initialize CURL." << std::endl;
    }

    curl_global_cleanup();
}

void Wrapper::SendJson(char *endpt, Json::Value body, Json::Value *buffer)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        struct MemoryStruct chunk;
        chunk.memory = (char *)malloc(1);
        chunk.size = 0;

        char *uri = (char *)malloc((strlen(rpc) + strlen(endpt) + 1) * sizeof(char));
        strcpy(uri, rpc);
        strcat(uri, endpt);

        curl_easy_setopt(curl, CURLOPT_URL, uri);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charsets: utf-8");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.asCString());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Wrapper::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK)
        {
            JSONCPP_STRING err;

            Json::CharReaderBuilder builder;
            const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
            if (!reader->parse(chunk.memory, chunk.memory + chunk.size, buffer, &err))
            {
                std::cout << "eth-rpc: Failed to parse JSON response." << std::endl;
            }
        }
        else
        {
            std::cout << "eth-rpc: Request failed." << std::endl;
        }

        free(uri);

        free(chunk.memory);
        curl_easy_cleanup(curl);
    }
    else
    {
        std::cout << "eth-rpc: Failed to initialize CURL." << std::endl;
    }

    curl_global_cleanup();
}