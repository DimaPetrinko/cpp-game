#pragma once

namespace Resources
{
	class Asset
	{
	protected:
		int mReferenceCount = 0;
	public:
		virtual ~Asset() = default;

		void IncreaseReferenceCount();
		void DecreaseReferenceCount();
		int GetReferenceCount() const;
	};
}
