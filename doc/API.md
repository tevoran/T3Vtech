# T3V-engine API

## Initializing the engine

The highest level of the engine API is implemented as a singleton and can therefore
be used with a reference in such a way

```cpp
t3v::engine& te=t3v::engine::get();
```

Once you have retrieved the engine class object then you have to choose and start a renderer.
If you don't choose one you will get error messages. And it is possible to choose different properties
of the engine until this point. You will activate them by starting the renderer

```cpp
te.start_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);
```

### Renderer flags

The software renderer uses
```cpp
TE_RENDERER_SOFTWARE_RASTERIZER
```
as its flag.

Once there are more renderers implemented, it is possible to switch your renderer on the fly.


## Using the API for information

### Getting current resolution

```cpp
te.get_resx(); //will return the resolution for the x-axis as an int
te.get_resy(); //will return the resolution for the y-axis as an int
```

## Assets

### Loading textures

Textures can be different file formats (at least BMP, JPG and PNG) and can be quite easily loaded and used.

```cpp
t3v::texture& load_texture(const char *path);
```

## Rendering

### Updating screen
For showing the current frame the engine's update function is used. It clears the screen to black
for the next frame as well.

It is important to note that the software renderer only starts to render when the update function is reached.
The regular object render calls just put the vertices into the waiting queue. This arises as a necessity as
synchronizing the render threads has a certain cost.

```cpp
te.update();
```


### Render mesh / vertices

To render any number of vertices you have to give a pointer of the vertices and their number
to the render function.

```cpp
void render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture); // function declaration

te.render(vertex, 6, &tex); //sample usage
```

### Object3D class

This is a class used for representing 3d objects. It 

```cpp
class object3d // the class name
```

It is possible to give a pointer of a bunch of vertices with the number of vertices to the class.

```cpp
void use_vertices(t3v::vertex *vertices_in, const int num_vertices);
```

The same thing is possible with a texture. A previously loaded texture can be given via a pointer to the class.
```cpp
void use_texture(t3v::texture *texture_in);
```

And finally an object can be rendered with its render method.
```cpp
void render();
```

#### Transformations

The object can be placed anywhere in the world with

```cpp
void position(glm::vec3 position);

test_obj.position({0,0,100}); //this would place the object at 0,0,100
```

Rotation can be used with the rotate function
```cpp
void rotate(glm::vec3 axis, float rotation_degrees);

test_obj.rotate({1,0,0}, 45); //This rotates an object 45 degrees around its x-axis
```

If you want to scale an object there are two caling functions available.
One is used for scaling an object along each of the three axes and the other one can be used for different
scaling values along different axes.

```cpp
void scale(float scale);  //uniform scaling
void scale(glm::vec3 scale); //more complex scaling

test_obj.scale(1.9);  //uniform scaling
test_obj.scale({1.3,1.2,1.5}); //more complex scaling
```
