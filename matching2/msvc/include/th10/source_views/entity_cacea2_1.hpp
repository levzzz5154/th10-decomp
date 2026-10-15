#pragma once


// Clears the "registered with the animation list" bit of one slot flag word.
// The retail constructor reaches every flag through a pointer, which keeps the
// store in the read-modify-write form the image uses.
