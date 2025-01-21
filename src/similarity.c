#include <math.h>
#include "similarity.h"

// Convert NCD value to similarity percentage (0-100)
double NCDToSimilarity(double ncd) {
    // NCD values typically range from 0 (identical) to ~1.1 (completely different)
    // We'll cap the NCD at 1.1 for normalization
    const double MAX_NCD = 1.1;
    
    // Clamp NCD value between 0 and MAX_NCD
    if (ncd < 0) ncd = 0;
    if (ncd > MAX_NCD) ncd = MAX_NCD;
    
    // Convert to similarity percentage:
    // - NCD = 0 -> 100% similar
    // - NCD = MAX_NCD -> 0% similar
    return (1.0 - (ncd / MAX_NCD)) * 100.0;
} 