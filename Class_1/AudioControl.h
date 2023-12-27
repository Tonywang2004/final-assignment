#pragma once
#ifndef __AUDIOCONTROL_H__
#define __AUDIOCONTROL_H__

#include "audio/include/AudioEngine.h"
using namespace std;

class AudioControl {
public:
    // 确保全局仅存在一个 AudioControl 实例
    // 设置静态单例
    static AudioControl* getInstance();

    // 播放背景音乐
    void playBackgroundMusic(const string& filename, bool loop = true);

    // 设置音量
    void setVolume(float volume);

    // 获取当前音量
    float getVolume() const;

    // 静音所有声音
    void muteAllSounds();

    // 取消静音所有声音
    void unmuteAllSounds();

    // 获取静音状态
    bool isMuted() const;
    
    //点击音效
    void setClickSoundEnabled(bool enabled);
    bool isClickSoundEnabled() const;
    void playClickSoundEffect();

private:
    // 构造函数
    AudioControl();

    // 设置静态指针
    static AudioControl* instance;

    // 背景音乐的音频ID
    int backgroundMusicID;

    // 当前音量
    float currentVolume;

    // 静音状态标志
    bool isMute;

    //点击音效标志
    bool isClickSound;
};

#endif 

