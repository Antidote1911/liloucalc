#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

namespace lil  // for Arsenic Preferences
{

// Global app infos
const QString APP_SHORT_NAME         = "LilouCalc";
const QString APP_VERSION            = "1.0";
const QString APP_NAME               = "LilouCalc_v"+APP_VERSION;
const QString APP_ORGANIZATION       = "Team1911";
const QString APP_URL                = "https://github.com/Antidote1911";

// Default app preferences
const QString DEFAULT_CRYPTO_ALGO    = "ChaCha20Poly1305";
const QString DEFAULT_HASH_ALGO      = "Whirlpool";
const QString DEFAULT_ENCODING       = "Base64_Encoder";

// Argon2 parameters
const uint32_t T_COST                = 4;      // n-pass computation
const uint32_t M_COST                = 1<<16;  // 64 MiB memory usage
const uint32_t PARALLELISM           = 2;      // number of threads and lanes

} // namespace lil

#endif // CONSTANTS_H
