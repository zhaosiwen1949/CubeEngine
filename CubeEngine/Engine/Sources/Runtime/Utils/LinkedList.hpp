//
//  LinkedList.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/23.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <stdio.h>
class LinkedList {
public:
    void PushBack(LinkedList* node);
    void Remove(LinkedList* node);
    virtual ~LinkedList();
    template <typename T>
    T* Next() {
        return (T*)_mNext;
    }
private:
    LinkedList* _mNext = nullptr;
};

#endif /* LinkedList_hpp */
