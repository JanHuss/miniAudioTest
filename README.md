# MiniAudioTest
A test application of running an audio engine in its simplest form. 

The previous engine architecture was tightly coupled, making it near impossible to expand the engine any further.
This engine is using a "patchwork" styled approach and only makes use of components whenever the components are needed. 
This engine will be extended on with the `Composite` pattern for a hierarchial structure, the `Object Pool` pattern for <br>
the handling of `Voices`, and the `Observer` pattern for the UI elements and parameter changes.
