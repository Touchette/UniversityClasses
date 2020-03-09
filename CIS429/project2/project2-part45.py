import m5
m5.util.addToPath('../')
from m5.objects import *
from caches import *
from common import SimpleOpts

SimpleOpts.set_usage("usage: %prog [options] <binary to execute>")
(opts, args) = SimpleOpts.parse_args()

# Default binary is matrix multiplication, allow user to choose
binary = "tests/test-progs/mm"
if len(args) == 1:
    binary = args[0]
elif len(args) > 1:
    SimpleOpts.print_help()
    m5.fatal("Expected a binary to execute as a positional argument")

'''
System setup first
'''
# System
system = System()

# Clock Domain
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = "1GHz"
system.clk_domain.voltage_domain =  VoltageDomain()

# Memory System
system.mem_mode = "timing"             # Use timing accesses
system.mem_ranges = [AddrRange("4GB")] # Create an address range

# CPU
system.cpu = DerivO3CPU()

# Memory Busses
system.l2bus = L2XBar()
system.membus = SystemXBar()

# *****************************************************************************
# L2 Cache Setup
# *****************************************************************************
# Create L1 shared instruction & data cache
system.l2cache = L2Cache(opts)

# Connect the shared cache to the CPU and membus
system.l2cache.connectCPUSideBus(system.l2bus)
system.l2cache.connectMemSideBus(system.membus)

# *****************************************************************************
# Split L1 Instruction and L1 Data Cache Setup
# *****************************************************************************
# Create L1 instruction and data cache
system.cpu.icache = L1ICache(opts)
system.cpu.dcache = L1DCache(opts)

# Connect the instruction and data caches to the CPU and bus
system.cpu.icache.connectCPU(system.cpu)
system.cpu.dcache.connectCPU(system.cpu)
system.cpu.icache.connectBus(system.l2bus)
system.cpu.dcache.connectBus(system.l2bus)

# Memory Controller & its connections
system.cpu.createInterruptController()
system.cpu.interrupts[0].pio = system.membus.master
system.cpu.interrupts[0].int_master = system.membus.slave
system.cpu.interrupts[0].int_slave = system.membus.master
system.system_port = system.membus.slave

# Memory
system.mem_ctrl = DDR3_1600_8x8()
system.mem_ctrl.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.master

'''
Process setup
'''
# Process
process = Process()
process.cmd = [binary]

# Set CPU to execute process
system.cpu.workload = process

# Create the execution threads
system.cpu.createThreads()

'''
Simulation environment setup
'''
# Root of the simulation
root = Root(full_system=False, system=system)

'''
Run the setup
'''
# Instantiating the simulator
m5.instantiate()

# Run the simulator, kick off discrete event simulation
exit_event = m5.simulate()
m5.stats.dump()

print("{} at tick {}.".format(exit_event.getCause(), m5.curTick()))
