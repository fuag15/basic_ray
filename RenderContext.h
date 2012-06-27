
#ifndef RenderContext_h
#define RenderContext_h

class Scene;

class RenderContext {
 public:
  RenderContext(  Scene* scene)
    : scene(scene)
  {
  }
  ~RenderContext() {
  }

    Scene* getScene()   {
    return scene;
  }
 private:
    Scene* scene;
};

#endif
