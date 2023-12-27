#include "AudioControl.h"
#include "audio/include/AudioEngine.h"
#include "cocos2d.h"
#include"hero.h"
USING_NS_CC;

// 确保全局仅存在一个 AudioControl 实例，以实现对全局的声音控制
// 初始化静态实例指针
AudioControl* AudioControl::instance = NULL;

// 返回 AudioControl 类的单一实例
AudioControl* AudioControl::getInstance() {
    // 如果实例不存在，则创建新实例
    if (instance == NULL) {
        instance = new AudioControl();
    }
    return instance;
}

// 构造函数，设置初始状态
AudioControl::AudioControl() : backgroundMusicID(-1), currentVolume(30.0f), isMute(false), isClickSound(true) {}

// 播放背景音乐
void AudioControl::playBackgroundMusic(const std::string& filename, bool loop) {
    if (backgroundMusicID != -1) {
        AudioEngine::stop(backgroundMusicID); // 停止当前播放的音乐
    }
   // 播放新的背景音乐并保存其ID
    backgroundMusicID = AudioEngine::play2d(filename, loop, currentVolume);
    isMute = false;
}

// 设置音量
void AudioControl::setVolume(float volume) {
    currentVolume = volume;
    if (backgroundMusicID != -1 ) {
        AudioEngine::setVolume(backgroundMusicID, volume); // 更新音量
    }
    isMute = false;
}

// 获取当前音量
float AudioControl::getVolume() const {
    return currentVolume;
}

// 静音
void AudioControl::muteAllSounds() {
    if (!isMute) {
        AudioEngine::setVolume(backgroundMusicID, 0); // 设置音量为 0 实现静音
        isMute = true;
    }
}

// 取消静音
void AudioControl::unmuteAllSounds() {
    AudioEngine::setVolume(backgroundMusicID, currentVolume); // 恢复音量
    isMute = false;
}

// 获取当前静音状态
bool AudioControl::isMuted() const {
    return isMute;
}

//同理，点击音效部分
void AudioControl::setClickSoundEnabled(bool enabled) {
    isClickSound = enabled;
}

bool AudioControl::isClickSoundEnabled() const {
    return !isClickSound;
}

void AudioControl::playClickSoundEffect() {
    if (isClickSound && !isMute) {
        AudioEngine::play2d("click_sound.mp3", false, currentVolume);
    }
}


