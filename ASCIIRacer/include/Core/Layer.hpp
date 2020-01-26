#pragma once

/// <summary>	Indica la posizione "z" di un GameObject. </summary>
///
/// <remarks>	Un GameObject con un Layer pi� alto verr�
/// 			disegnato sopra uno con un layer pi� basso. </remarks>

enum class Layer
{
	Overlay = 5,
	Foreground_1 = 4,
	Foreground_2 = 3,
	Content = 2,
	Background_1 = 1,
	Background_2 = 0
};