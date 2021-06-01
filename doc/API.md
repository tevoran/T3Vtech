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
