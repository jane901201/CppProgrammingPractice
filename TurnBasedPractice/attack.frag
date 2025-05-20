#version 330 core

in vec2 vTexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;
uniform float uTime;         // 時間経過
uniform float uIntensity;    // エフェクトの強さ（例：0.0〜1.0）

void main() {
    // 斬撃風にUVを揺らす（X方向にノイズっぽく）
    float offset = sin(vTexCoord.y * 30.0 + uTime * 10.0) * 0.01 * uIntensity;
    vec2 displacedUV = vec2(vTexCoord.x + offset, vTexCoord.y);

    // テクスチャの色
    vec4 texColor = texture(uTexture, displacedUV);

    // 上下で透明になるグラデーション
    float alphaMask = smoothstep(0.0, 0.2, vTexCoord.y) * smoothstep(1.0, 0.8, vTexCoord.y);

    // 斬撃風に白っぽく光る
    vec3 highlight = mix(texColor.rgb, vec3(1.0), 0.3 * uIntensity);

    FragColor = vec4(highlight, texColor.a * alphaMask * uIntensity);
}
