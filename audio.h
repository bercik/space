#ifndef AUDIO_H
#define AUDIO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

enum AUDIO_TYPE { AT_EXPLOSION, AT_RESTART, AT_TRANSPORT, AT_WHIZ, AT_NUMBER_OF_TYPES };

typedef struct
{
    ALLEGRO_SAMPLE* samples[AT_NUMBER_OF_TYPES];
    ALLEGRO_SAMPLE* song_sample;
    ALLEGRO_SAMPLE_INSTANCE* song_sample_instance;
}Audio;

// LoadSamples: ładuje dźwięki
void LoadSamples(Audio* const audio);
// DestroySamples: usuwa dźwięki z pamięci
void DestroySamples(Audio* const audio);
// Play: odtwarza dźwięk o podanym typie
void Play(const Audio* const audio, enum AUDIO_TYPE audio_type);
// PlaySong: rozpoczyna odtwarzanie muzyki tła
void PlaySong(Audio* const audio);
// StopSong: zatrzymuje odtwarzanie muzyki tła
void StopSong(Audio* const audio);

#endif
