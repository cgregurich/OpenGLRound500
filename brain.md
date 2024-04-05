Questions I haven't yet figured out:
* why when there's an issue in the vert shader (layout location is too high), it causes
the triangle to be displayed in the correct spot but black? the vertex shader is related 
to position, and the frag shader color, so why is the position okay but the colors not?
https://pastebin.com/cUxQ8Hjd

* why do you need to use the shader program (glUseProgram()) before changing the
uniform value (glUniform3f()) but you dont need to use the program before grabbing
 the uniform values location (glGetUniformLocation())?
