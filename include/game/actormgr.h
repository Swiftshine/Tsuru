#pragma once

#include "sead.h"
#include "actor/stageactor.h"

class ActorBuffer { // Size: 0x18
public:
    ActorBuffer();

    BaseActor* findActorByID(u32* id);

    sead::Buffer<BaseActor*> mBuffer;
    u32 mUsedCount;
    BaseActor** mLast;
    u32 _10;
    u8 _14;
};

class ActorMgr {
public:
    BaseActor* create(ActorBuildInfo* pBuildInfo, u32 addToActive);
    BaseActor* instanciateActor(ActorBuildInfo* pBuildInfo, bool notDefer);
    
    u32 createActor(BaseActor* actor);  // Calls "create" virtual functions


    sead::IDisposer disposer;
    sead::UnitHeap* playerUnitHeap;
    sead::UnitHeap* actorUnitHeap;
    u8 deferredActorCreations[0x5970]; // sead::FixedRingBuffer<ActorBuildInfo, 520>
    sead::OffsetList<BaseActor> actorsToCreate;
    sead::OffsetList<BaseActor> actorsToDelete;
    sead::OffsetList<BaseActor> activeActors;
    sead::OffsetList<BaseActor> drawableActors;
    sead::FixedPtrArray<sead::Heap, 520> deletedActorHeaps;
    sead::FixedPtrArray<BaseActor, 520> finalExecuteList;
    ActorBuffer actors;
    // ...

    static ActorMgr* sInstance;
};