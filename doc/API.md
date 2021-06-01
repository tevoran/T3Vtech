# T3V-engine API

## Initializing the engine

The highest level of the engine API is implemented as a singleton and can therefore
be used with a reference in such a way

```cpp
t3v::engine& te=t3v::engine::get();
```

Once you have retrieved the engine class object then you have to choose a renderer.
If you don't choose one you will get error messages.

```cpp
te.choose_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);
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
te.resx(); //will return the resolution for the x-axis as an int
te.resy(); //will return the resolution for the y-axis as an int
```

## Rendering
For showing the current frame the engine's update function is used.

```cpp
te.update();
```
