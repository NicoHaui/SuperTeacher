//
// Created by samuel on 31.03.16.
//

#pragma once

class AbstractView {
public:
    virtual void draw(void);
    virtual void processEvent(int envent);
    virtual void activate(void);
    virtual void deactivate(void);
};
