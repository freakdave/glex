/* KallistiOS ##version##

   dc/sound/sfxmgr.h
   Copyright (C) 2002 Dan Potter

*/

/** \file   dc/sound/sfxmgr.h
    \brief  Basic sound effect support.

    This file contains declarations for doing simple sound effects. This code is
    only usable for simple WAV files containing either 16-bit samples (stereo or
    mono) or Yamaha ADPCM (4-bits, stereo or mono). Also, all sounds played in
    this manner must be at most 65534 samples in length, as this does not handle
    buffer chaining or anything else complex. For more interesting stuff, you
    should probably look at the sound stream stuff instead.

    \author Dan Potter
*/

#ifndef __DC_SOUND_NSFXMGR_H
#define __DC_SOUND_NSFXMGR_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/** \brief  Sound effect handle type.

    Each loaded sound effect will be assigned one of these, which is to be used
    for operations related to the effect, including playing it or unloading it.
*/
typedef uint32 sfxhnd_t;

/** \brief  Invalid sound effect handle value.

    If a sound effect cannot be loaded, this value will be returned as the error
    condition.
*/
#define NSFXHND_INVALID 0

/** \brief  Load a sound effect.

    This function loads a sound effect from a WAV file and returns a handle to
    it. The sound effect can be either stereo or mono, and must either be 16-bit
    uncompressed PCM samples or 4-bit Yamaha ADPCM.

    \param  fn              The file to load.
    \return                 A handle to the sound effect on success. On error,
                            NSFXHND_INVALID is returned.
*/
sfxhnd_t nsnd_sfx_load(const char *fn);

/** \brief  Unload a sound effect.

    This function unloads a previously loaded sound effect, and frees the memory
    associated with it.

    \param  idx             A handle to the sound effect to unload.
*/
void nsnd_sfx_unload(sfxhnd_t idx);

/** \brief  Unload all loaded sound effects.

    This function unloads all previously loaded sound effect, and frees the
    memory associated with them.
*/
void nsnd_sfx_unload_all();

/** \brief  Play a sound effect.

    This function plays a loaded sound effect with the specified volume (for
    both stereo or mono) and panning values (for mono sounds only).

    \param  idx             The handle to the sound effect to play.
    \param  vol             The volume to play at (between 0 and 255).
    \param  pan             The panning value of the sound effect. 0 is all the
                            way to the left, 128 is center, 255 is all the way
                            to the right.

    \return                 The channel used to play the sound effect (or the
                            left channel in the case of a stereo sound, the
                            right channel will be the next one) on success, or
                            -1 on failure.
*/
int nsnd_sfx_play(sfxhnd_t idx, int vol, int pan);

/** \brief  Play a sound effect on a specific channel.

    This function works similar to nsnd_sfx_play(), but allows you to specify the
    channel to play on. No error checking is done with regard to the channel, so
    be sure its safe to play on that channel before trying.

    \param  chn             The channel to play on (or in the case of stereo,
                            the left channel).
    \param  idx             The handle to the sound effect to play.
    \param  vol             The volume to play at (between 0 and 255).
    \param  pan             The panning value of the sound effect. 0 is all the
                            way to the left, 128 is center, 255 is all the way
                            to the right.

    \return                 chn
*/
int nsnd_sfx_play_chn(int chn, sfxhnd_t idx, int vol, int pan);

/** \brief  Stop a single channel of sound.

    This function stops the specified channel of sound from playing. It does no
    checking to make sure that a sound effect is playing on the channel
    specified, and thus can be used even if you're using the channel for some
    other purpose than sound effects.

    \param  chn             The channel to stop.
*/
void nsnd_sfx_stop(int chn);

/** \brief  Stop all channels playing sound effects.

    This function stops all channels currently allocated to sound effects from
    playing. It does not affect channels allocated for use by something other
    than sound effects..
*/
void nsnd_sfx_stop_all();

/** \brief  Allocate a sound channel for use outside the sound effect system.

    This function finds and allocates a channel for use for things other than
    sound effects. This is useful for, for instance, the streaming code.

    \returns                The allocated channel on success, -1 on failure.
*/
int nsnd_sfx_chn_alloc();

/** \brief  Free a previously allocated channel.

    This function frees a channel that was allocated with nsnd_sfx_chn_alloc(),
    returning it to the pool of available channels for sound effect use.

    \param  chn             The channel to free.
*/
void nsnd_sfx_chn_free(int chn);

__END_DECLS

#endif  /* __DC_SOUND_NSFXMGR_H */

