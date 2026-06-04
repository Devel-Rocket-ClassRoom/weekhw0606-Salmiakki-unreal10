#pragma once

bool IsFloatEqual(float Num1, float Num2);

/// <summary>
/// 0.0f ~ 1.0f 사이를 리턴하는 함수
/// </summary>
/// <returns>0.0f ~ 1.0f 사이의 랜덤값</returns>
float GetRandom();

/// <summary>
/// Min ~ Max 사이의 랜덤한 값을 리턴하는 함수
/// </summary>
/// <param name="Min">랜덤의 최소값(포함)</param> 
/// <param name="Max">랜덤의 최대값(포함)</param>
/// <returns>Min ~ Max 사이의 랜덤한 값</returns>
int GetRandomRange(int Min, int Max);
//