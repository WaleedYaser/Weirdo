#ifndef ZERO_EXPORT_H
#define ZERO_EXPORT_H

#ifdef __cplusplus
	#define ZERO_API extern "C" __declspec(dllexport)
#else
	#define ZERO_API __declspec(dllexport)
#endif

#endif /* ZERO_EXPORT_H */
