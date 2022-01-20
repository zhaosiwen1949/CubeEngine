//
//  LinkedList.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/23.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "LinkedList.hpp"

LinkedList::~LinkedList() {
    _mNext = nullptr;
}

void LinkedList::PushBack(LinkedList* node) {
    if(_mNext == nullptr) {
        _mNext = node;
    } else {
        if(_mNext == node) {
            return;
        }
        _mNext->PushBack(node);
    }
}

void LinkedList::Remove(LinkedList* node) {
    if(_mNext != nullptr) {
        if(_mNext == node) {
            _mNext = node->Next<LinkedList>();
            delete node;
        } else {
            _mNext->Remove(node);
        }
    }
}
