#ifndef KURO_OS_EXPORT_H
#define KURO_OS_EXPORT_H

#ifdef KURO_CPLUSPLUS
	#define KURO_EXPORT extern "C" __declspec(dllexport)
#else
	#define KURO_EXPORT __declspec(dllexport)
#endif

#endif /* KURO_OS_EXPORT_H */
