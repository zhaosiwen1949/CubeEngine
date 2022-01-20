//
//  Application.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/11.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include "../Object/World.hpp"

class Application {
public:
    virtual int     Initialize() noexcept;
    virtual void    Render() noexcept;
    virtual void    Run() noexcept;
    virtual void    Finalize() noexcept;
    virtual void    Quit() noexcept;
    virtual bool    IsQuit() noexcept;
public:
    inline World* GetWorld() const {
        return _mWorld;
    };
    
private:
    bool _mQuit = false;
    World* _mWorld;
};

#endif /* Application_hpp */
