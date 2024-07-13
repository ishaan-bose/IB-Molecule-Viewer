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
#define     LIGHT_DIRECTIONAL       0
#define     LIGHT_POINT             1

struct Light {
    int enabled;
    int type;
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
    vec3 viewD = normalize(viewPos - fragPosition);

    vec2 uv = vec2(0.0);


    
    if (lights[0].enabled == 1)
    {
        vec3 light = vec3(0.0);

        if (lights[0].type == LIGHT_DIRECTIONAL)
        {
           light = -normalize(lights[0].target - lights[0].position);
        }

        if (lights[0].type == LIGHT_POINT)
        {
            light = normalize(lights[0].position - fragPosition);
        }

        float NdotL = max(dot(normal, light), 0.0);
        lightDot += lights[0].color.rgb*NdotL;

        //got this line of code from https://roystan.net/articles/toon-shader/
        uv = vec2(1.0 - (NdotL * 0.5 + 0.5), 0.5);      
    }
    

    texelColor = texture(texture0, uv);

    finalColor += texelColor;
    finalColor += texelColor*(ambient/10.0)*colDiffuse;

    //for the rim it should be black, if the dot product of the normal and viewDirection is smaller than some value
    //then it means that the surface is facing almost 90 degrees or more than 90 degrees
    if(dot(viewD, normal) < 0.23)
    {
        finalColor = vec4(0.0, 0.0, 0.0, 1.0);
    }



    
}