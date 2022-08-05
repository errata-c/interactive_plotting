Inspired by desmos, nice easy graphing, with few distractions.

Interactive and fast as well. Would like to have the ability to actively display values, label things, and create nice parametric things.

Simple window, document as input. The window should auto update when the document is changed. (get_write_time cpp filesytem) loop over the input document checking periodically.

Syntax? Perhaps just simple python with some custom classes and a predefined control flow or context.

- Predefine the initial scale for the grid, and draw it first.
- Create a number of simple methods for creating functions.
- Allow the viewport to be panned, zoomed, asymmetric scales, reset.
- Allow for variables to be sliders within a range, buttons, operations
- Put all the Graphing in the right side of the viewport, put all the UI in the left side panel.
- Make the side panel a tree like structure for display.

For each frame:

Check the current input file to see if it was changed. Verify that it parses without any issues. Once it has run, take the objects defined and add them to the list of drawing objects. Additionally allow for variables with control handles or sliders.

Decide on the grid spacing to draw given the viewport zoom level (Consider the two axes separately). Draw the grid, given the current viewport. Draw each of the render objects in the order they were defined. 



**Context:** store the data about the current scene. The file we are tracking, the zoom, the pan, the object list.

Create a simple SFML window. Keep it in the context, update the viewport as needed when the user changes it.