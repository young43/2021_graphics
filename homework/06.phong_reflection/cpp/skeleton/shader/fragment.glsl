#version 120                  // GLSL 1.20

varying   vec3 position_wc;
varying   vec3 normal_wc;

// for phong shading
uniform vec3 u_light_position;
uniform vec3 u_light_ambient;
uniform vec3 u_light_diffuse;
uniform vec3 u_light_specular;

uniform vec3 u_camera_position;

uniform vec3  u_obj_ambient;
uniform vec3  u_obj_diffuse;
uniform vec3  u_obj_specular;
uniform float u_obj_shininess;

vec3 directional_light() 
{
  vec3 color = vec3(0.0);
  vec3 light_dir = normalize(u_light_position);

  // ambient
  color += (u_light_ambient * u_obj_ambient);
  
  // diffuse 
  float ndotl = max(dot(normal_wc, light_dir), 0.0);
  color += (ndotl * u_light_diffuse * u_obj_diffuse);

  // specular
  vec3 view_dir = normalize(u_camera_position - position_wc);
  vec3 reflect_dir = reflect(-light_dir, normal_wc); 

  float rdotv = max(dot(view_dir, reflect_dir), 0.0);
  color += (pow(rdotv, u_obj_shininess) * u_light_specular * u_obj_shininess);

  return color;
}

void main()
{
	gl_FragColor = vec4(directional_light(), 1.0);
}