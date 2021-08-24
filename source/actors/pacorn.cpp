#include <game/actor/stage/powerup.h>

class PAcorn : public Powerup {
public:
    PAcorn(const ActorBuildInfo* buildInfo);
    virtual ~PAcorn() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    void vf18C() override;
    void playBlockReleaseUpAnim() override;
    void playBlockReleaseDownAnim() override;
    void playIdleAnim() override;
    void playFloatAnim() override;
    void vf1B4() override;
    u32 vf1C4() override;
    void vf1FC() override;
};

const Profile PAcornProfile(&PAcorn::build, ProfileID::PAcorn, "PAcorn", nullptr, 16406);
PROFILE_RESOURCES(ProfileID::PAcorn, "I_musasabi");

PAcorn::PAcorn(const ActorBuildInfo* buildInfo)
    : Powerup(buildInfo)
{ }

Actor* PAcorn::build(const ActorBuildInfo* buildInfo) {
    return new PAcorn(buildInfo);
}

u32 PAcorn::onCreate() {
    this->_1827 = true;
    this->_1808 = 0;
    this->mModel = ModelWrapper::create("I_musasabi", "I_musasabiP", 1, 1, 0, 0, 0);

    this->setupActor();
    this->spawnMethod();
    this->updateModel();

    return 1;
}

u32 PAcorn::onExecute() {
    this->mStates.execute();
    // FUN_0232a958((this->_)._.unk6 + 0x28); //? Possibly ActorScaler related
    this->updateModel();
    this->deleteActorWhenOutOfView(0);
    this->FUN_2518f94();
    this->FUN_25183ac();

    return 1;
}

void PAcorn::vf18C() {
    this->doStateChange(&StateID_PowerupState1);
}

void PAcorn::playBlockReleaseUpAnim() {
    this->mModel->playSklAnim("out", 1);
}


void PAcorn::playBlockReleaseDownAnim() {
    this->mModel->playSklAnim("out3", 3);
}

void PAcorn::playIdleAnim() {
    this->mModel->playSklAnim("wait", 4);
}

void PAcorn::playFloatAnim() {
    this->mModel->playSklAnim("wait2", 5);
}

void PAcorn::vf1B4() {
    this->mModel->playSklAnim("out2", 2);
}

u32 PAcorn::vf1C4() {
    u32 local;

    if (FUN_25196e8(&local, PowerupStatePAcorn, 1) != 0)
        return FUN_2519580(local, this->_1830);

    else return 0;
}

void PAcorn::vf1FC() {
    this->doStateChange(&StateID_PowerupState1);
}
 