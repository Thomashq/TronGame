#version 330 core

out vec4 FragColor;  // A cor de saída do fragmento

uniform vec3 objectColor;  // Cor do objeto (ex: cor da arena ou das motos)
uniform vec3 lightColor;   // Cor da luz

void main()
{
    // Aplica uma multiplicação simples entre a cor do objeto e a cor da luz
    vec3 result = lightColor * objectColor;
    FragColor = vec4(result, 1.0);  // Define a cor final do fragmento
}
