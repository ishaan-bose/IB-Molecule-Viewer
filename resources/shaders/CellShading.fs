#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
//in vec4 fragColor;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

#define     MAX_LIGHTS              1   //for now

struct Light
{
    vec3 position;
    vec3 target;
    vec4 color;
};

// Input lighting values
uniform Light lights[MAX_LIGHTS];
uniform vec4 ambient;
uniform vec3 viewPos;

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = vec4(0.0);
    vec3 lightDot = vec3(0.0);
    vec3 normal = normalize(fragNormal);
    vec3 viewD = normalize(fragPosition - viewPos);

    vec2 uv = vec2(0.0); 
    vec3 light = vec3(0.0);


    light = -normalize(lights[0].target - lights[0].position);


    float NdotL = max(dot(normal, light), 0.0);

    //got this line of code from https://roystan.net/articles/toon-shader/
    texelColor = texture(texture0, vec2(1.0 - (NdotL * 0.5 + 0.5), 0.5));

    finalColor += texelColor + (ambient/10.0)*colDiffuse;

    //for the rim it should be black, if the dot product of the normal and viewDirection is smaller than some value
    //then it means that the surface is facing almost 90 degrees or more than 90 degrees
    if(abs(dot(viewD, normal)) < 0.10)
    {
        finalColor = vec4(0.0, 0.0, 0.0, 1.0);
    }



    
}