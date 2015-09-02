#ifndef __SOUND_H__
#define __SOUND_H__


#include <map>
#include <memory>
#include <iostream>
#include <string>
#include <SDL_mixer.h>
#include <algorithm> 

using std::shared_ptr;

class Sound {
public:
    explicit Sound();
    void LoadSounds();
    
    void PlayMusic(const std::string& name);
    void PlaySfx(const std::string& name);

private:
    void LoadMusic(const std::string& name, const std::string& filename);
    void LoadSfx(const std::string& name, const std::string& filename);

private:
    std::map<std::string, Mix_Chunk*> m_sfx;
    std::map<std::string, Mix_Music*> m_music;
};

typedef shared_ptr<Sound> SoundPtr;

#endif /* __SOUND_H__ */

