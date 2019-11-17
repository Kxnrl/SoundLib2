#if defined _soundlib2_ext_included
  #endinput
#endif
#define _soundlib2_ext_included

methodmap SoundFile < Handle
{
    /* 
     *  Open a sound file.
     *
     * @param path          The path of sound file.
     * @param valve_fs      Open file via IFileSystem. (helpful for map music)
     *
     * @return              sound hanld. if sound has been opened, but does not close, 
     *                      u will get null handle when you trying to open twice.
     * @error               if can not create dummy file. trhow an error.
    */
    public native SoundFile(const char[] path, bool value_file_system = false);
    
    /* 
     *  Retrieve sound length in float.
     *
     * @return              value of sound length. @(-1.0 if failure)
     * 
     * @error               if invalid sound handle given. trhow an error.
    */
	property int Length
    {
        // getter
        public native get();
    }
    
    /* 
     *  Retrieve sound length in milliseconds.
     *
     * @return              value of sound length. @(-1 if failure)
     * 
     * @error               if invalid sound handle given. trhow an error.
    */
	property int LengthInMilliseconds
    {
        // getter
        public native get();
    }
    
    /* 
     *  Retrieve sound bitrate.
     *
     * @return              value of sound bitrate. @(-1 if failure)
     * 
     * @error               if invalid sound handle given. trhow an error.
    */
	property int BitRate
    {
        // getter
        public native get();
    }

    /* 
     *  Retrieve sound sampling rate.
     *
     * @return              value of sound sampling rate. @(-1 if failure)
     * 
     * @error               if invalid sound handle given. trhow an error.
    */
	property int SamplingRate
    {
        // getter
        public native get();
    }
};

/**
 * Opens a sound file.
 *
 * @note Sound files are closed with delete operator.
 *
 * @param file                File to open
 * @param valve if true, path is opened in Valve Filesystem.
 * @return                    A Handle to the sound file, null on open error.
 */
native SoundFile OpenSoundFile(const char[] path, bool valve=false);

/**
 * Gets the length of the sound file in seconds
 *
 * @param hndl            Handle to the sound file.
 * @return                T     The song length in seconds
 */
native int GetSoundLength(SoundFile soundfile);

/**
 * Gets the length of the sound file in milliseconds
 *
 * @param hndl            Handle to the sound file.
 * @return                The song length in milliseconds
 */
native int GetSoundLengthInMilliseconds(SoundFile soundfile);

/**
 * Get the Bit rate of sound (kbps)
 *
 * @param hndl            Handle to the sound file
 * @return                sound bitrate (int)
 */
native int GetSoundBitrate(SoundFile soundfile);

/**
 * Get the Sampling rate of sound (hz)
 *
 * @param hndl            Handle to the sound file
 * @return                sampling rate (int)
 */
native int GetSoundSamplingRate(SoundFile soundfile);

/**
 * Do not edit below this line!
 */
public Extension __ext_soundlib2 = 
{
	name = "SoundLib2",
	file = "soundlib2.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};

#if !defined REQUIRE_EXTENSIONS
public void __ext_soundlib2_SetNTVOptional()
{
	MarkNativeAsOptional("SoundFile.SoundFile");
	MarkNativeAsOptional("SoundFile.Length.get");
	MarkNativeAsOptional("SoundFile.LengthInMilliseconds.get");
	MarkNativeAsOptional("SoundFile.Bitrate.get");
	MarkNativeAsOptional("SoundFile.SamplingRate.get");

	MarkNativeAsOptional("OpenSoundFile");
	MarkNativeAsOptional("GetSoundLength");
	MarkNativeAsOptional("GetSoundLengthInMilliseconds");
	MarkNativeAsOptional("GetSoundBitrate");
	MarkNativeAsOptional("GetSoundSamplingRate");
}
#endif