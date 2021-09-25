#include "Asset.h"

namespace Resources
{
	void Asset::IncreaseReferenceCount()
	{
		++mReferenceCount;
	}

	void Asset::DecreaseReferenceCount()
	{
		if (--mReferenceCount < 0) mReferenceCount = 0;
	}

	int Asset::GetReferenceCount() const
	{
		return mReferenceCount;
	}
}
