#pragma once
#include "Actor.h"
#include "List.h"

class ActorManager {
    private:
        List<Actor*> actorList;

    public:
        void createNewActor(); 
};
