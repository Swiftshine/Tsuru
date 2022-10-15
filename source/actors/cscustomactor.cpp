#include "game/actor/courseselect/cscollisionactor.h"
#include "game/csplayermgr.h"
#include "game/actor/actormgr.h"
#include "game/graphics/model/modelnw.h"
#include "game/csscriptmgr.h"
#include "game/savemgr.h"
#include "log.h"

class CSCustomActor : public CSCollisionActor {
    SEAD_RTTI_OVERRIDE_IMPL(CSCustomActor, CSCollisionActor)

public:
    CSCustomActor(const ActorBuildInfo* buildInfo);
    virtual ~CSCustomActor() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void onCSScriptCommandUpdate() override;

    ModelWrapper* model;

    static const CSHitboxCollider::Info sCollisionInfo;
};

//? Uncomment this line to enable the custom actor.
//const Profile CSCustomActorProfile(&CSCustomActor::build, 856);

const CSHitboxCollider::Info CSCustomActor::sCollisionInfo = {
    240.0f,      // Size
    Vec3f(0.0f)  // Offset
};

CSCustomActor::CSCustomActor(const ActorBuildInfo* buildInfo)
    : CSCollisionActor(buildInfo)
{ }

Actor* CSCustomActor::build(const ActorBuildInfo* buildInfo) {
    return new CSCustomActor(buildInfo);
}

u32 CSCustomActor::onCreate() {
    this->model = ModelWrapper::create("cobStarGate", "cobStarGate", 3);

    this->hitboxCollider.init(this, &CSCustomActor::sCollisionInfo);

    return 1;
}

u32 CSCustomActor::onExecute() {
    // This needs to be in onExecute for the collision check below to work so it's probably not "add"
    CSHitboxColliderMgr::instance()->add(&this->hitboxCollider);

    this->updateCSScriptInteractions();

    // Checks if player collided
    if (CSHitboxColliderMgr::instance()->FUN_21c5894(&this->hitboxCollider)) {
        PRINT("Player collided");

        // Do a hack to get the colliding player
        CourseSelectActor* collidingPlayer = reinterpret_cast<CourseSelectActor*>(ActorMgr::instance()->actors.findActorByID(CSPlayerMgr::instance()->playerActorID));

        // Mess with it
        //collidingPlayer->position.y += 0.2f;
    }

    return 1;
}

u32 CSCustomActor::onDraw() {
    Mtx34 mtx;

    mtx.makeRTIdx(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();

    this->model->draw();

    return 1;
}

void CSCustomActor::onCSScriptCommandUpdate() {
    u32 command;

    CSScriptMgr::instance()->getCurrentScriptCommandType(&command);

    PRINT(command);
}
