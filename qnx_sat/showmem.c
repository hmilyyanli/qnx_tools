#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/syspage.h>

void asinfo_func()
{
    struct asinfo_entry *entries = SYSPAGE_ENTRY(asinfo);
        size_t count = SYSPAGE_ENTRY_SIZE(asinfo) / sizeof(struct asinfo_entry);
        char *strings = SYSPAGE_ENTRY(strings)->data;

        uint64_t total = 0;
        size_t i;
        for (i = 0; i < count; i++) {
                struct asinfo_entry *entry = &entries[i];
                if (strcmp(strings + entry->name, "ram") == 0) {
                        total += entry->end - entry->start + 1;
                }
        }

        printf("Total: %llu\n", total);

}

void cpuinfo_func()
{
	struct cpuinfo_entry *entries = SYSPAGE_ENTRY(cpuinfo);
	printf("cpuid %x, flags %x\n",entries->cpu,entries->flags);
}

int
main(int argc, char *argv[])
{
	if(!strcmp(argv[1],"asinfo"))
		asinfo_func();
	else if(!strcmp(argv[1],"cpuinfo"))
		cpuinfo_func();
	else
		printf("usage: ./a.out xxxinfo");
	return 0;
}
