#ifndef HEADER_OPENHOME_MEDIA_SOURCE
#define HEADER_OPENHOME_MEDIA_SOURCE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Standard.h>

namespace OpenHome {
namespace Media {

class Track;
class IPlayer;

class Source : public Observable
{
public:
    static const TUint kMaxTypeBytes = 20;
    static const TUint kMaxNameBytes = 20;

public:
    bool Details(Bwx& aSystemName, Bwx& aType, Bwx& aName); //returns Visibility boolean
    void SetName(const Brx& aValue);
    void SetVisible(bool aValue);
    void SetHandle(uint32_t aHandle);

public:
    //Requests from Providers to Source.  These call the Player's
    //implementation with appropriate info filled in.  
    virtual void Play(const Track* aTrack, uint32_t aSecond);
    virtual void Play(int32_t aRelativeIndex);
    virtual void PlaySecondAbsolute(uint32_t aSecond);
    virtual void PlaySecondRelative(int32_t aSecond);
    virtual void Pause();
    virtual void Stop();
    virtual void Deleted(uint32_t aId, const Track* aReplacement);
    virtual uint32_t NewId();

public:
    //Callbacks from the Renderer via the Player to be implemented by the derived class
    virtual const Track* GetTrack(uint32_t aId, int32_t aOffset) = 0;
    virtual void Buffering(uint32_t aId) = 0;
    virtual void Stopped(uint32_t aId) = 0;
    virtual void Paused(uint32_t aId) = 0;
    virtual void Playing(uint32_t aId) = 0;

protected:
    Source(const Brx& aSystemName, const Brx& aType, const Brx& aName, bool aVisible, IPlayer& aPlayer);


private:
    friend class ProviderProduct;
    void SetModifiable(ILockable& aLockable, IObserver& aObserver);
private:
    Bws<kMaxNameBytes> iSystemName;
    Bws<kMaxTypeBytes> iType;
    Bws<kMaxNameBytes> iName;
    bool iVisible;
    ILockable* iLockable;
    uint32_t iHandle;
    IPlayer& iPlayer;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_OPENHOME_MEDIA_SOURCE

