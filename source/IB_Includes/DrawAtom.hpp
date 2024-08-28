#include "rlgl.h"
#include "raylib.h"
#include "raymath.h"

#include "Atom.hpp"
#include <vector>

#define MAX_MATERIAL_MAPS       12

namespace IBMol
{
    //copied this from the DrawMeshInstanced function, modified it a bit

    void DrawSmoAtom_PX_OrbitalInstanced(Mesh mesh, Material material, std::vector<IBMol::SmolAtom>& AtomsVector, int instances)
    {
    #if defined(GRAPHICS_API_OPENGL_33) || defined(GRAPHICS_API_OPENGL_ES2)
        // Instancing required variables
        float16 *instanceTransforms = NULL;
        unsigned int instancesVboId = 0;

        // Bind shader program
        rlEnableShader(material.shader.id);

        // Send required data to shader (matrices, values)
        //-----------------------------------------------------
        // Upload to shader material.colDiffuse
        if (material.shader.locs[SHADER_LOC_COLOR_DIFFUSE] != -1)
        {
            float values[4] = {
                (float)material.maps[MATERIAL_MAP_DIFFUSE].color.r/255.0f,
                (float)material.maps[MATERIAL_MAP_DIFFUSE].color.g/255.0f,
                (float)material.maps[MATERIAL_MAP_DIFFUSE].color.b/255.0f,
                (float)material.maps[MATERIAL_MAP_DIFFUSE].color.a/255.0f
            };

            rlSetUniform(material.shader.locs[SHADER_LOC_COLOR_DIFFUSE], values, SHADER_UNIFORM_VEC4, 1);
        }

        // Upload to shader material.colSpecular (if location available)
        if (material.shader.locs[SHADER_LOC_COLOR_SPECULAR] != -1)
        {
            float values[4] = {
                (float)material.maps[SHADER_LOC_COLOR_SPECULAR].color.r/255.0f,
                (float)material.maps[SHADER_LOC_COLOR_SPECULAR].color.g/255.0f,
                (float)material.maps[SHADER_LOC_COLOR_SPECULAR].color.b/255.0f,
                (float)material.maps[SHADER_LOC_COLOR_SPECULAR].color.a/255.0f
            };

            rlSetUniform(material.shader.locs[SHADER_LOC_COLOR_SPECULAR], values, SHADER_UNIFORM_VEC4, 1);
        }

        // Get a copy of current matrices to work with,
        // just in case stereo render is required, and we need to modify them
        // NOTE: At this point the modelview matrix just contains the view matrix (camera)
        // That's because BeginMode3D() sets it and there is no model-drawing function
        // that modifies it, all use rlPushMatrix() and rlPopMatrix()
        Matrix matModel = MatrixIdentity();
        Matrix matView = rlGetMatrixModelview();
        Matrix matModelView = MatrixIdentity();
        Matrix matProjection = rlGetMatrixProjection();

        // Upload view and projection matrices (if locations available)
        if (material.shader.locs[SHADER_LOC_MATRIX_VIEW] != -1) rlSetUniformMatrix(material.shader.locs[SHADER_LOC_MATRIX_VIEW], matView);
        if (material.shader.locs[SHADER_LOC_MATRIX_PROJECTION] != -1) rlSetUniformMatrix(material.shader.locs[SHADER_LOC_MATRIX_PROJECTION], matProjection);

        // Create instances buffer
        instanceTransforms = (float16 *)RL_MALLOC(instances*sizeof(float16));

        // Fill buffer with instances transformations as float16 arrays
        for (int i = 0; i < instances; i++)
        {
            //IB comment, different from all the other comments made by raysan5:
            //yes I know that accessing all the elements of a vector each frame is slow, but unless you are running on something
            //like a really potato cpu, you should be good to go 👍
            IBMol::SmolAtom cur = AtomsVector[i];
            //remember that order of multiplication matters
            Matrix PxTransform = MatrixScale(1.0/5.3597, 1.0/5.3597, 1.0/5.3597);
            //i am really just hoping the compiler optimizes a lot of this code for me

            instanceTransforms[i] = MatrixToFloatV(PxTransform);
        }

        // Enable mesh VAO to attach new buffer
        rlEnableVertexArray(mesh.vaoId);

        // This could alternatively use a static VBO and either glMapBuffer() or glBufferSubData().
        // It isn't clear which would be reliably faster in all cases and on all platforms,
        // anecdotally glMapBuffer() seems very slow (syncs) while glBufferSubData() seems
        // no faster, since we're transferring all the transform matrices anyway
        instancesVboId = rlLoadVertexBuffer(instanceTransforms, instances*sizeof(float16), false);

        // Instances transformation matrices are send to shader attribute location: SHADER_LOC_MATRIX_MODEL
        for (unsigned int i = 0; i < 4; i++)
        {
            rlEnableVertexAttribute(material.shader.locs[SHADER_LOC_MATRIX_MODEL] + i);
            rlSetVertexAttribute(material.shader.locs[SHADER_LOC_MATRIX_MODEL] + i, 4, RL_FLOAT, 0, sizeof(Matrix), (void *)(i*sizeof(Vector4)));
            rlSetVertexAttributeDivisor(material.shader.locs[SHADER_LOC_MATRIX_MODEL] + i, 1);
        }

        rlDisableVertexBuffer();
        rlDisableVertexArray();

        // Accumulate internal matrix transform (push/pop) and view matrix
        // NOTE: In this case, model instance transformation must be computed in the shader
        matModelView = MatrixMultiply(rlGetMatrixTransform(), matView);

        // Upload model normal matrix (if locations available)
        if (material.shader.locs[SHADER_LOC_MATRIX_NORMAL] != -1) rlSetUniformMatrix(material.shader.locs[SHADER_LOC_MATRIX_NORMAL], MatrixTranspose(MatrixInvert(matModel)));
        //-----------------------------------------------------

        // Bind active texture maps (if available)
        for (int i = 0; i < MAX_MATERIAL_MAPS; i++)
        {
            if (material.maps[i].texture.id > 0)
            {
                // Select current shader texture slot
                rlActiveTextureSlot(i);

                // Enable texture for active slot
                if ((i == MATERIAL_MAP_IRRADIANCE) ||
                    (i == MATERIAL_MAP_PREFILTER) ||
                    (i == MATERIAL_MAP_CUBEMAP)) rlEnableTextureCubemap(material.maps[i].texture.id);
                else rlEnableTexture(material.maps[i].texture.id);

                rlSetUniform(material.shader.locs[SHADER_LOC_MAP_DIFFUSE + i], &i, SHADER_UNIFORM_INT, 1);
            }
        }

        // Try binding vertex array objects (VAO)
        // or use VBOs if not possible
        if (!rlEnableVertexArray(mesh.vaoId))
        {
            // Bind mesh VBO data: vertex position (shader-location = 0)
            rlEnableVertexBuffer(mesh.vboId[0]);
            rlSetVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_POSITION], 3, RL_FLOAT, 0, 0, 0);
            rlEnableVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_POSITION]);

            // Bind mesh VBO data: vertex texcoords (shader-location = 1)
            rlEnableVertexBuffer(mesh.vboId[1]);
            rlSetVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_TEXCOORD01], 2, RL_FLOAT, 0, 0, 0);
            rlEnableVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_TEXCOORD01]);

            if (material.shader.locs[SHADER_LOC_VERTEX_NORMAL] != -1)
            {
                // Bind mesh VBO data: vertex normals (shader-location = 2)
                rlEnableVertexBuffer(mesh.vboId[2]);
                rlSetVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_NORMAL], 3, RL_FLOAT, 0, 0, 0);
                rlEnableVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_NORMAL]);
            }

            // Bind mesh VBO data: vertex colors (shader-location = 3, if available)
            if (material.shader.locs[SHADER_LOC_VERTEX_COLOR] != -1)
            {
                if (mesh.vboId[3] != 0)
                {
                    rlEnableVertexBuffer(mesh.vboId[3]);
                    rlSetVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_COLOR], 4, RL_UNSIGNED_BYTE, 1, 0, 0);
                    rlEnableVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_COLOR]);
                }
                else
                {
                    // Set default value for unused attribute
                    // NOTE: Required when using default shader and no VAO support
                    float value[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
                    rlSetVertexAttributeDefault(material.shader.locs[SHADER_LOC_VERTEX_COLOR], value, SHADER_ATTRIB_VEC4, 4);
                    rlDisableVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_COLOR]);
                }
            }

            // Bind mesh VBO data: vertex tangents (shader-location = 4, if available)
            if (material.shader.locs[SHADER_LOC_VERTEX_TANGENT] != -1)
            {
                rlEnableVertexBuffer(mesh.vboId[4]);
                rlSetVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_TANGENT], 4, RL_FLOAT, 0, 0, 0);
                rlEnableVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_TANGENT]);
            }

            // Bind mesh VBO data: vertex texcoords2 (shader-location = 5, if available)
            if (material.shader.locs[SHADER_LOC_VERTEX_TEXCOORD02] != -1)
            {
                rlEnableVertexBuffer(mesh.vboId[5]);
                rlSetVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_TEXCOORD02], 2, RL_FLOAT, 0, 0, 0);
                rlEnableVertexAttribute(material.shader.locs[SHADER_LOC_VERTEX_TEXCOORD02]);
            }

            if (mesh.indices != NULL) rlEnableVertexBufferElement(mesh.vboId[6]);
        }

        int eyeCount = 1;
        if (rlIsStereoRenderEnabled()) eyeCount = 2;

        for (int eye = 0; eye < eyeCount; eye++)
        {
            // Calculate model-view-projection matrix (MVP)
            Matrix matModelViewProjection = MatrixIdentity();
            if (eyeCount == 1) matModelViewProjection = MatrixMultiply(matModelView, matProjection);
            else
            {
                // Setup current eye viewport (half screen width)
                rlViewport(eye*rlGetFramebufferWidth()/2, 0, rlGetFramebufferWidth()/2, rlGetFramebufferHeight());
                matModelViewProjection = MatrixMultiply(MatrixMultiply(matModelView, rlGetMatrixViewOffsetStereo(eye)), rlGetMatrixProjectionStereo(eye));
            }

            // Send combined model-view-projection matrix to shader
            rlSetUniformMatrix(material.shader.locs[SHADER_LOC_MATRIX_MVP], matModelViewProjection);

            // Draw mesh instanced
            if (mesh.indices != NULL) rlDrawVertexArrayElementsInstanced(0, mesh.triangleCount*3, 0, instances);
            else rlDrawVertexArrayInstanced(0, mesh.vertexCount, instances);
        }

        // Unbind all bound texture maps
        for (int i = 0; i < MAX_MATERIAL_MAPS; i++)
        {
            if (material.maps[i].texture.id > 0)
            {
                // Select current shader texture slot
                rlActiveTextureSlot(i);

                // Disable texture for active slot
                if ((i == MATERIAL_MAP_IRRADIANCE) ||
                    (i == MATERIAL_MAP_PREFILTER) ||
                    (i == MATERIAL_MAP_CUBEMAP)) rlDisableTextureCubemap();
                else rlDisableTexture();
            }
        }

        // Disable all possible vertex array objects (or VBOs)
        rlDisableVertexArray();
        rlDisableVertexBuffer();
        rlDisableVertexBufferElement();

        // Disable shader program
        rlDisableShader();

        // Remove instance transforms buffer
        rlUnloadVertexBuffer(instancesVboId);
        RL_FREE(instanceTransforms);
    #endif
    }
} // namespace IBMol
