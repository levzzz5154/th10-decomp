#include "th10/app/version_marker.hpp"

#include <cstdio>

// 0x00420100 - opens/probes the th10.dat archive, then loads the generated
// version marker ("th10_0100a.ver"). The loaded pointer and byte count are
// published together. Both failure paths emit the retail diagnostic and
// return -1; a present marker returns 0.
int VersionMarker_Load(VersionMarkerEnv* env) {
	if (!env->probe("th10.dat")) {
		env->log(env->missing_probe_log);
		return -1;
	}

	char name[128];
	std::snprintf(name, sizeof(name), "th10_%.4x%c.ver", env->version,
	              env->suffix);
	std::size_t size = 0;
	unsigned char* data = env->load(name, &size);
	*env->published_data = data;
	*env->published_size = size;
	if (data != 0) {
		return 0;
	}

	// Retail explicitly republishes null before logging the load failure.
	*env->published_data = 0;
	env->log(env->load_failure_log);
	return -1;
}
