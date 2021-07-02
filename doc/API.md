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
TE_RENDERER_SOFTWARE_RASTERIZER //for using all available cpu threads (useful for 3D)
TE_RENDERER_SOFTWARE_RASTERIZER_SINGLE_THREAD //for using only one cpu thread (useful for 2D only)
```
as its flag.

Once there are more renderers implemented, it is possible to switch your renderer on the fly.


### Engine properties

Between getting the engine reference and starting the engine there is the possibility to configure the
according to the users needs. Although some of them might be overwritten later, as the player might add
an extern engine configuration to make a game runnable on an old computer.

#### FPS Counter

It is possible and sometimes useful to activate an FPS counter.
This can be done after retrieving the engine singleton with the function

```cpp
te.activate_fps_counter(true, &font);

```

Although you have to take of previously loading a font otherwise the render can't render the counter.
This means as well that the counter can only be activated after the start of the renderer.

#### Window properties

To set the resolution of the window the following two functions can be used.
```cpp
void set_resx(int resx);
void set_resy(int resy);

//example
te.set_resx(1920);
te.set_resy(1080);
```

And to toggle fullscreen mode the set_fullscreen() function is used.

```cpp
void set_fullscreen(bool set_fullscreen);

//example
te.set_fullscreen(true);
```

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

#### Primitives

Primitives are the objects that the engine can generate without relying on extern meshes.
They can be created once a an Object3D object is created. Its properties or its texture can be set
afterwards in the regular way of doing things.

##### Quad

```cpp
void make_quad(float width, float height); //creating quad primitive

test_obj.make_quad(float width, float height); //creating quad primitive
```
##### Cube

```cpp
void make_cube(float size); //create simple cube

test_obj.make_cube(float size); //creating simple cube
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

## 2D Stuff

### Text

It is possible to print text that stays on the screen for exactly one frame. It is helpful for printing always changing information onto the screen.

### Loading Font

To be able to print text. It is first necessary to create a font object. Otherwise the engine is not able to print anything.

```cpp
t3v::font font(const char *path_to_font); //example

t3v::font font("../assets/fonts/OpenSans-Regular.ttf"); //example

```

### Printing a Single Frame Text

The print_single_frame function is used when you have to put something on the screen but the text needs to change often.
An example would be an FPS counter or other fast changing data.

```cpp
void print_single_frame(std::string text, t3v::font& font, t3v::color color_in, int font_size, int x, int y);


//example
//the function belongs to the engine class
//and take care to use the previously loaded font
te.print_single_frame("T3Vtech - software renderer", font, {10,240,10, 255}, 32, te.get_resx()-430, te.get_resy()-48);

```

### Object2D Class

The object2d class is used for 2d sprites. They can be copied if desired.

An instance of this class can be created by using the following code.

```cpp
t3v::object2d cat;
```

As this wouldn't be renderable by itself, you need to add some more data.

#### Loading Sprite from Disk

It is necessary to load an image file from the disk. It is a seperate object from
the object2D class. But can be used in as many instances of object2D as necessary. 

```cpp
t3v::sprite cat_sprite("../assets/cat.png");
```

Usable image file formats are at least BMP, JPG and PNG.

After the sprite is loaded it can be connected with an object2D by using the following
code.

```cpp
cat.use_sprite(cat_sprite);

```

If the object is copied afterwards the same sprite will be used in the copy as well.
It is not necessary to reload it again.

If the sprite exists at the end of its scope then the used data will be free'd 
automatically.

#### Position

The sprite can be positioned on the screen in absolute screen coordinates (pixels)
by using the position method. It simply takes two integers as its parameters.

```cpp
cat.position(100, 200); //Draw the cat at the location 100x200 on the screen
```

#### Scaling

If the image's base size doesn't fit your needs you can rescale it. The scaling
happens relative to the image's base size and takes a float paremeter.

```cpp
cat.scale(4.5); //the cat is now 4.5 times it's original size
```

#### Rendering the Sprite

And finally if everything necessary is set then sprite can be rendered onto the
screen by calling its render method.

```cpp
cat.render(); //show the cat

```