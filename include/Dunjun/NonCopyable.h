#ifndef DUNJUN_NONCOPYABLE_H
#define DUNJUN_NONCOPYABLE_H

namespace Dunjun
{
	class NonCopyable
	{
	protected:
		NonCopyable() {}
	private:
		NonCopyable(const NonCopyable &) = delete;
		NonCopyable& operator=(const NonCopyable &) = delete;
	};
} // namespace Dunjun

#endif//DUNJUN_NONCOPYABLE_H