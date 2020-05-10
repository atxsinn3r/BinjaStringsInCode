#include <iostream>
#include <cstring>
#include "binaryninjaapi.h"

using namespace BinaryNinja;
using namespace std;

void run(BinaryView *view, uint64_t start, uint64_t length) {
    for (auto str : view->GetStrings()) {
        uint64_t strAddr = str.start;
        vector<ReferenceSource> xrefs = view->GetCodeReferences(strAddr);
        if (xrefs.empty()) {
            continue;
        }
        void* buf = calloc(str.length+1, sizeof(char));
        view->Read(buf, strAddr, str.length);
        stringstream message;
        message << hex << strAddr << " : ";
        message << (char*) buf;
        free(buf);
        LogInfo("%s", message.str().c_str());
    }
}

extern "C" {
BINARYNINJAPLUGIN bool CorePluginInit() {
    PluginCommand::RegisterForRange("String References in Code", "Finds strings that are referenced by code", &run);
    return true;
}
}