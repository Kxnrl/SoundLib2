#include "extension.h"

#define TAGLIB_STATIC
#include "soundfile.h"
#include "systemfilestream.h"
#include "valvefilestream.h"

extern HandleType_t g_SoundFileType;

static cell_t OpenSoundFile(IPluginContext *pContext, const cell_t *params) {
	char *filename;
	pContext->LocalToString(params[1], &filename);

	TagLib::IOStream *stream;
	if (params[2]) {
		stream = ValveFileStream::Open(filename, "rb");
	}
	else {
		stream = SystemFileStream::Open(filename, "rb");
	}
	if (!stream) {
		return 0;
	}
	auto sf = SoundFile::Open(stream);
	if (!sf) {
		delete stream;
		return 0;
	}
	return handlesys->CreateHandle(g_SoundFileType, (void*)sf, pContext->GetIdentity(), myself->GetIdentity(), NULL);
}

static cell_t GetSoundLength(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile *sf;
	if ((err = handlesys->ReadHandle(hndl, g_SoundFileType, &sec, (void **)&sf))
		!= HandleError_None)
	{
		pContext->ReportError("Invalid sound-file handle %x (error %d)", hndl, err);
		return 0;
	}

	return sf->length();
}

static cell_t GetSoundLengthInMilliseconds(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile *sf;
	if ((err = handlesys->ReadHandle(hndl, g_SoundFileType, &sec, (void **)&sf))
		!= HandleError_None)
	{
		pContext->ReportError("Invalid sound-file handle %x (error %d)", hndl, err);
		return 0;
	}

	return sf->lengthInMilliseconds();
}

static cell_t GetSoundBitrate(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile *sf;
	if ((err = handlesys->ReadHandle(hndl, g_SoundFileType, &sec, (void **)&sf))
		!= HandleError_None)
	{
		pContext->ReportError("Invalid sound-file handle %x (error %d)", hndl, err);
		return 0;
	}

	return sf->bitrate();
}

static cell_t GetSoundSamplingRate(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile *sf;
	if ((err = handlesys->ReadHandle(hndl, g_SoundFileType, &sec, (void **)&sf))
		!= HandleError_None)
	{
		pContext->ReportError("Invalid sound-file handle %x (error %d)", hndl, err);
		return 0;
	}

	return sf->sampleRate();
}

sp_nativeinfo_t g_Natives[] =
{
	{ "OpenSoundFile", OpenSoundFile },
	{ "GetSoundLength", GetSoundLength },
	{ "GetSoundLengthInMilliseconds", GetSoundLengthInMilliseconds },
	{ "GetSoundBitrate", GetSoundBitrate },
	{ "GetSoundSamplingRate", GetSoundSamplingRate },
	{ NULL,	NULL },
};