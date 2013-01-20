// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// CpuClass
//		Controls counter for CPU usage display
#pragma once


// |----------------------------------------------------------------------------|
// |							      Linking									|
// |----------------------------------------------------------------------------|
#pragma comment(lib, "pdh.lib")


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <pdh.h>


// |----------------------------------------------------------------------------|
// |						     Class: CpuClass								|
// |----------------------------------------------------------------------------|
class CpuClass
{
public:

	//|-------------------------------Public Functions--------------------------|
	
	// Constructors and Destructors
	CpuClass();
	CpuClass(const CpuClass&);
	~CpuClass();
	
	// Initiallizes the object
	void Initialize();

	// Performs shutdown, memory releasing, and cleanup
	void Shutdown();

	// Called once each frame render
	void Frame();

	// Getter functions
	int GetCpuPercentage();

private:
	
	//|-----------------------------Private Data Members------------------------|
	bool m_canReadCpu;
	HQUERY m_queryHandle;
	HCOUNTER m_counterHandle;
	unsigned long m_lastSampleTime;
	long m_cpuUsage;

};