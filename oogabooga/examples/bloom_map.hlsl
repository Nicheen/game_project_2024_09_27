#include "GlobalShaders.hlsl"

float4 get_light_contribution(PS_INPUT input) {
	float2 vertex_pos = input.position_screen.xy;  // In pixels
    vertex_pos.y = window_size.y - vertex_pos.y; // For some reason D3D11 inverts the Y here, so we need to revert it

	float4 total_light_contribution = float4(0, 0, 0, 1);

	for (int i = 0; i < light_count; i++) {
		LightSource light = lights[i];

		// Calculate distance between the vertex and the light source
		float dist = length(light.position - vertex_pos);

		if (dist > light.radius) continue; // Skip pixels outside of the light radius

		// Calculate attenuation based on distance and radius
		float attenuation = saturate(1.0 - (dist / light.radius)) * light.intensity;

		// Accumulate light contribution
		total_light_contribution.rgb += attenuation;
	}

	return total_light_contribution;
}

float4 pixel_shader_extension(PS_INPUT input, float4 color) {
	// We want to output everything above 1.0

	color = color + get_light_contribution(input);
	
	return float4(
		max(color.r-1.0, 0),
		max(color.g-1.0, 0),
		max(color.b-1.0, 0),
		color.a
	);
}