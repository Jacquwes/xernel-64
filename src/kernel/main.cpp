#include <limine.h>

static volatile struct limine_framebuffer_request framebuffer_request =
{
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0,
};

void halt()
{
	asm("cli");
	for (;;)
		asm("hlt");
}

void main()
{
	if (framebuffer_request.response == NULL
		|| framebuffer_request.response->framebuffer_count < 1)
		return;

	limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

	for (size_t i = 0; i < 100; i++)
	{
		uint32_t* fb = framebuffer->address;
		fb[i * (framebuffer->pitch / 4) + i] = 0xffffff;
	}

	return;
}