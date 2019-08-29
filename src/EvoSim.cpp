//
#include "../include/EvoSim.h"


// define static flag to stop the sim
bool EvoSim::flag_isrunning = true;

void sighandler(int sig)
{
    std::cout << "Signal " << sig << " caught..." << std::endl;
    std::cout << "Stopping simulation..." << std::endl;
    EvoSim::flag_isrunning = false;
}


//////////////////////////////////////////////////

EvoSim::EvoSim()
{    
    // create default world
    m_pworld = std::make_shared<World>();
    std::cout << "EvoSim using world: " << m_pworld->m_str_name << std::endl;

    // TODO idea
    // Run sim until all agents died
    // Remember x most successful (in terms of age) genes
    // Remember genes for each category (predator, food harvest, highest reproduction..)
    // Restart using these genes

}

EvoSim::~EvoSim()
{

}


void EvoSim::initialise()
{
    signal(SIGABRT, &sighandler);
    signal(SIGTERM, &sighandler);
    signal(SIGINT, &sighandler);
 
    // create ros publisher
    //m_ros_publisher = m_ros_nodehandle.advertise<std_msgs::String>("evosim_status", 1);
}

void EvoSim::stop()
{
    EvoSim::flag_isrunning = false;
}

/////////////////////////////////////////////////////

void EvoSim::iteration()
{
    using namespace std::chrono_literals;

    while(EvoSim::flag_isrunning)
    {
        // TODO use Boost logging
        //std::cout << "iterating" << std::endl;

        // handle user commands
        // TODO

        // update world
        m_pworld->update(0.100);

        // publish current simulation status
        //m_ros_publisher.publish( simulation status  ); TODO

        // check if all agents have died
        int num_alive, num_dead = 0;
        get_number_agents(num_alive, num_dead);

        static int mod_ten = 0;
        if(mod_ten % 10 == 0)
        {
            std::cout << "EvoSim:: Alive agents: " << num_alive << std::endl;
        }
        mod_ten ++;

        if( num_alive <= 0 )
        {
            std::cout << "EvoSim:: All agents died, applying natural "
                            << "selection, creating new agents." << std::endl;
            // all agents died, sample the most successful ones
            // and restart after applying some mutation
            std::vector< std::shared_ptr<Agent> > next_generation_agents;
            create_new_agents(m_pworld->m_vpagents, next_generation_agents,
                                            5, 0.05);
            // clear current agents
            m_pworld->m_vpagents.clear();
            m_pworld->m_vpagents.insert(
                    std::end(m_pworld->m_vpagents),
                    std::begin(next_generation_agents),
                    std::end(next_generation_agents));

            // restore world
            m_pworld->restore();
        }

        // update display
        display.display(m_pworld);

        std::this_thread::sleep_for(10ms);
    }
 }
	
bool EvoSim::run()
{
    initialise();

    std::thread d(&EvoSim::iteration, this);
    d.join();

    return true;
}

//////////////////////////////////////////////////////

void EvoSim::get_number_agents(int & num_alive, int & num_dead)
{
    num_alive = 0;
    num_dead = 0;
    for(const auto agent : m_pworld->m_vpagents)
    {
        if(agent->alive)
            num_alive ++;
        else
            num_dead ++;
    }
}

void EvoSim::create_new_agents(std::vector< std::shared_ptr<Agent> > current_agents,
								std::vector< std::shared_ptr<Agent> > & new_agents,
								const unsigned int num_agents,
								const double mutation_mod)
{
    std::sort ( std::begin(current_agents), std::end(current_agents), Agent::compare_by_age );
    
    double highest_age = current_agents.at(0)->state.age;
    std::cout << "EvoSim:: Highes age: " << highest_age << std::endl;
    
    unsigned int count = 0;
    for (auto agent : current_agents)
    {
        AgentData::Genes genes 
         = agent->genes;
        AgentData::Genes_neural_weights genes_neural_weights
         = agent->genes_neural_weights;
        
        // apply mutation
        genes.mutate(mutation_mod);
        genes_neural_weights.mutate(mutation_mod);
        
        // create new Agent with new genes
        std::shared_ptr<Agent> new_agent
         = std::make_shared<Agent>(genes, genes_neural_weights);
        new_agents.push_back(new_agent);
        ++ count;
        if (count >= num_agents)
            break;
    }
}

int EvoSim::calculate_score(AgentData::State state)
{
    // For now simply go by age
    return std::round(state.age);
}