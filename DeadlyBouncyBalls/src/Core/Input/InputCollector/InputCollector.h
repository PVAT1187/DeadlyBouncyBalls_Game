#ifndef INPUT_COLLECTOR_H
#define INPUT_COLLECTOR_H

class Renderer;
struct Input;

class InputCollector
{
	public:
		Input collect(Renderer& renderer) const;
};

#endif // !INPUT_COLLECTOR_H

