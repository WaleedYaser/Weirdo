#ifndef KURO_EXPORT_H
#define KURO_EXPORT_H

#ifdef __cplusplus
	#define KURO_API extern "C" __declspec(dllexport)
#else
	#define KURO_API __declspec(dllexport)
#endif

#endif /* KURO_EXPORT_H */
