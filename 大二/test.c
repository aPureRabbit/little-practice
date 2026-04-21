#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_PROCESSES 10
#define MAX_NAME_LEN 10
#define TIME_QUANTUM 2

typedef struct {
    char name[MAX_NAME_LEN];
    int arrival_time;
    int service_time;
    int priority;
    int remaining_time;
    int start_time;
    int finish_time;
    int waiting_time;
    float response_ratio;
    int completed;
} Process;

typedef struct {
    Process processes[MAX_PROCESSES];
    int count;
    int current_time;
    char gantt_chart[1000];
} Scheduler;

// 函数声明
void init_scheduler(Scheduler *scheduler);
void read_processes_from_file(Scheduler *scheduler, const char *filename);
void reset_processes(Scheduler *scheduler);
void print_processes(Scheduler *scheduler);
void print_results(Scheduler *scheduler, const char *algorithm_name);
void calculate_metrics(Scheduler *scheduler, float *avg_turnaround, 
                      float *avg_weighted_turnaround, float *avg_waiting, float *avg_response);

// 调度算法
void fcfs(Scheduler *scheduler);
void sjf(Scheduler *scheduler);
void psa(Scheduler *scheduler);
void hrrn(Scheduler *scheduler);
void rr(Scheduler *scheduler, int time_quantum);
void preemptive_priority(Scheduler *scheduler);

// 工具函数
int all_completed(Scheduler *scheduler);
Process* get_next_arrival(Scheduler *scheduler, int current_time);
void add_to_gantt(Scheduler *scheduler, const char *process_name, int start, int end);

int main() {
    Scheduler scheduler;
    
    // 读取进程数据
    read_processes_from_file(&scheduler, "processes.txt");
    
    printf("读取的进程信息:\n");
    printf("%-10s %-10s %-10s %-10s\n", "进程名", "到达时间", "服务时间", "优先级");
    print_processes(&scheduler);
    
    // 测试各种调度算法
    printf("\n==========================");
    printf("\nFCFS调度算法\n");
    printf("===========================\n");
    fcfs(&scheduler);
    print_results(&scheduler, "FCFS");
    reset_processes(&scheduler);

    printf("\n==========================");
    printf("\nSJF调度算法\n");
    printf("===========================\n");
    sjf(&scheduler);
    print_results(&scheduler, "SJF");
    reset_processes(&scheduler);

    printf("\n==========================");
    printf("\nPSA调度算法\n");
    printf("===========================\n");
    psa(&scheduler);
    print_results(&scheduler, "PSA");
    reset_processes(&scheduler);

    printf("\n==========================");
    printf("\nHRRN调度算法\n");
    printf("===========================\n");
    hrrn(&scheduler);
    print_results(&scheduler, "HRRN");
    reset_processes(&scheduler);

    printf("\n==========================");
    printf("\nRR调度算法 (时间片=%d)\n", TIME_QUANTUM);
    printf("===========================\n");
    rr(&scheduler, TIME_QUANTUM);
    print_results(&scheduler, "RR");
    reset_processes(&scheduler);

    printf("\n\" \"=\"60 \"=");
    printf("\n优先级抢占式调度算法\n");
    printf("=\"60 \"=\n");
    preemptive_priority(&scheduler);
    print_results(&scheduler, "Preemptive Priority");
    
    // 测试RR算法不同时间片
    printf("\n\" \"=\"60 \"=");
    printf("\nRR算法不同时间片比较\n");
    printf("=\"60 \"=\n");
    int time_quanta[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) {
        reset_processes(&scheduler);
        rr(&scheduler, time_quanta[i]);
        
        float avg_turnaround, avg_weighted_turnaround, avg_waiting, avg_response;
        calculate_metrics(&scheduler, &avg_turnaround, &avg_weighted_turnaround, 
                         &avg_waiting, &avg_response);
        
        printf("\n时间片大小 = %d:\n", time_quanta[i]);
        printf("  平均周转时间: %.2f\n", avg_turnaround);
        printf("  平均带权周转时间: %.2f\n", avg_weighted_turnaround);
        printf("  平均等待时间: %.2f\n", avg_waiting);
        printf("  平均响应时间: %.2f\n", avg_response);
        printf("  调度序列: %s\n", scheduler.gantt_chart);
    }
    
    return 0;
}

void init_scheduler(Scheduler *scheduler) {
    scheduler->count = 0;
    scheduler->current_time = 0;
    strcpy(scheduler->gantt_chart, "");
}

void read_processes_from_file(Scheduler *scheduler, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // 创建示例文件
        file = fopen(filename, "w");
        if (file != NULL) {
            fprintf(file, "# 进程名 到达时间 服务时间 优先级\n");
            fprintf(file, "P1 0 5 3\n");
            fprintf(file, "P2 1 3 1\n");
            fprintf(file, "P3 2 8 4\n");
            fprintf(file, "P4 3 6 2\n");
            fprintf(file, "P5 4 4 5\n");
            fclose(file);
            printf("已创建示例文件 %s\n", filename);
        }
        file = fopen(filename, "r");
    }
    
    if (file == NULL) {
        printf("错误: 无法打开文件 %s\n", filename);
        exit(1);
    }
    
    char line[100];
    init_scheduler(scheduler);
    
    while (fgets(line, sizeof(line), file)) {
        // 跳过注释行和空行
        if (line[0] == '#' || line[0] == '\n') continue;
        
        Process p;
        p.completed = 0;
        p.start_time = -1;
        
        if (sscanf(line, "%s %d %d %d", p.name, &p.arrival_time, 
                   &p.service_time, &p.priority) == 4) {
            p.remaining_time = p.service_time;
            p.waiting_time = 0;
            p.response_ratio = 0.0;
            scheduler->processes[scheduler->count++] = p;
        }
    }
    
    fclose(file);
}

void reset_processes(Scheduler *scheduler) {
    for (int i = 0; i < scheduler->count; i++) {
        scheduler->processes[i].remaining_time = scheduler->processes[i].service_time;
        scheduler->processes[i].start_time = -1;
        scheduler->processes[i].finish_time = -1;
        scheduler->processes[i].waiting_time = 0;
        scheduler->processes[i].response_ratio = 0.0;
        scheduler->processes[i].completed = 0;
    }
    scheduler->current_time = 0;
    strcpy(scheduler->gantt_chart, "");
}

void print_processes(Scheduler *scheduler) {
    for (int i = 0; i < scheduler->count; i++) {
        Process *p = &scheduler->processes[i];
        printf("%-10s %-10d %-10d %-10d\n", p->name, p->arrival_time, 
               p->service_time, p->priority);
    }
}

void calculate_metrics(Scheduler *scheduler, float *avg_turnaround, 
                      float *avg_weighted_turnaround, float *avg_waiting, float *avg_response) {
    float total_turnaround = 0, total_weighted_turnaround = 0;
    float total_waiting = 0, total_response = 0;
    int completed_count = 0;
    
    for (int i = 0; i < scheduler->count; i++) {
        Process *p = &scheduler->processes[i];
        if (p->completed) {
            int turnaround = p->finish_time - p->arrival_time;
            float weighted_turnaround = (float)turnaround / p->service_time;
            int response_time = p->start_time - p->arrival_time;
            
            total_turnaround += turnaround;
            total_weighted_turnaround += weighted_turnaround;
            total_waiting += p->waiting_time;
            total_response += response_time;
            completed_count++;
        }
    }
    
    if (completed_count > 0) {
        *avg_turnaround = total_turnaround / completed_count;
        *avg_weighted_turnaround = total_weighted_turnaround / completed_count;
        *avg_waiting = total_waiting / completed_count;
        *avg_response = total_response / completed_count;
    } else {
        *avg_turnaround = *avg_weighted_turnaround = *avg_waiting = *avg_response = 0;
    }
}

void print_results(Scheduler *scheduler, const char *algorithm_name) {
    printf("\n%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-12s\n", 
           "进程名", "到达时间", "服务时间", "优先级", "开始时间", "完成时间", "周转时间", "带权周转");
    
    for (int i = 0; i < scheduler->count; i++) {
        Process *p = &scheduler->processes[i];
        if (p->completed) {
            int turnaround = p->finish_time - p->arrival_time;
            float weighted_turnaround = (float)turnaround / p->service_time;
            
            printf("%-10s %-10d %-10d %-10d %-10d %-10d %-10d %-12.2f\n", 
                   p->name, p->arrival_time, p->service_time, p->priority,
                   p->start_time, p->finish_time, turnaround, weighted_turnaround);
        }
    }
    
    float avg_turnaround, avg_weighted_turnaround, avg_waiting, avg_response;
    calculate_metrics(scheduler, &avg_turnaround, &avg_weighted_turnaround, 
                     &avg_waiting, &avg_response);
    
    printf("\n性能指标:\n");
    printf("平均周转时间: %.2f\n", avg_turnaround);
    printf("平均带权周转时间: %.2f\n", avg_weighted_turnaround);
    printf("平均等待时间: %.2f\n", avg_waiting);
    printf("平均响应时间: %.2f\n", avg_response);
    printf("\n调度序列: %s\n", scheduler->gantt_chart);
}

int all_completed(Scheduler *scheduler) {
    for (int i = 0; i < scheduler->count; i++) {
        if (!scheduler->processes[i].completed) return 0;
    }
    return 1;
}

void add_to_gantt(Scheduler *scheduler, const char *process_name, int start, int end) {
    char temp[100];
    if (strlen(scheduler->gantt_chart) > 0) {
        sprintf(temp, " -> %s(%d-%d)", process_name, start, end);
    } else {
        sprintf(temp, "%s(%d-%d)", process_name, start, end);
    }
    strcat(scheduler->gantt_chart, temp);
}

// FCFS调度算法
void fcfs(Scheduler *scheduler) {
    // 按到达时间排序
    for (int i = 0; i < scheduler->count - 1; i++) {
        for (int j = 0; j < scheduler->count - i - 1; j++) {
            if (scheduler->processes[j].arrival_time > scheduler->processes[j + 1].arrival_time) {
                Process temp = scheduler->processes[j];
                scheduler->processes[j] = scheduler->processes[j + 1];
                scheduler->processes[j + 1] = temp;
            }
        }
    }
    
    scheduler->current_time = 0;
    
    for (int i = 0; i < scheduler->count; i++) {
        Process *p = &scheduler->processes[i];
        
        if (scheduler->current_time < p->arrival_time) {
            scheduler->current_time = p->arrival_time;
        }
        
        p->start_time = scheduler->current_time;
        p->waiting_time = scheduler->current_time - p->arrival_time;
        scheduler->current_time += p->service_time;
        p->finish_time = scheduler->current_time;
        p->completed = 1;
        
        add_to_gantt(scheduler, p->name, p->start_time, p->finish_time);
    }
}

// SJF调度算法
void sjf(Scheduler *scheduler) {
    scheduler->current_time = 0;
    int completed = 0;
    
    while (completed < scheduler->count) {
        // 找到已到达且未完成的进程中服务时间最短的
        int shortest_index = -1;
        int shortest_time = INT_MAX;
        
        for (int i = 0; i < scheduler->count; i++) {
            Process *p = &scheduler->processes[i];
            if (!p->completed && p->arrival_time <= scheduler->current_time) {
                if (p->service_time < shortest_time) {
                    shortest_time = p->service_time;
                    shortest_index = i;
                }
            }
        }
        
        if (shortest_index != -1) {
            Process *p = &scheduler->processes[shortest_index];
            p->start_time = scheduler->current_time;
            p->waiting_time = scheduler->current_time - p->arrival_time;
            scheduler->current_time += p->service_time;
            p->finish_time = scheduler->current_time;
            p->completed = 1;
            completed++;
            
            add_to_gantt(scheduler, p->name, p->start_time, p->finish_time);
        } else {
            // 没有进程到达，时间前进到下一个进程到达时间
            int next_arrival = INT_MAX;
            for (int i = 0; i < scheduler->count; i++) {
                if (!scheduler->processes[i].completed && 
                    scheduler->processes[i].arrival_time < next_arrival) {
                    next_arrival = scheduler->processes[i].arrival_time;
                }
            }
            if (next_arrival != INT_MAX) {
                scheduler->current_time = next_arrival;
            }
        }
    }
}

// PSA调度算法
void psa(Scheduler *scheduler) {
    scheduler->current_time = 0;
    int completed = 0;
    
    while (completed < scheduler->count) {
        // 找到已到达且未完成的进程中优先级最高的（数字越小优先级越高）
        int highest_priority_index = -1;
        int highest_priority = INT_MAX;
        
        for (int i = 0; i < scheduler->count; i++) {
            Process *p = &scheduler->processes[i];
            if (!p->completed && p->arrival_time <= scheduler->current_time) {
                if (p->priority < highest_priority) {
                    highest_priority = p->priority;
                    highest_priority_index = i;
                }
            }
        }
        
        if (highest_priority_index != -1) {
            Process *p = &scheduler->processes[highest_priority_index];
            p->start_time = scheduler->current_time;
            p->waiting_time = scheduler->current_time - p->arrival_time;
            scheduler->current_time += p->service_time;
            p->finish_time = scheduler->current_time;
            p->completed = 1;
            completed++;
            
            add_to_gantt(scheduler, p->name, p->start_time, p->finish_time);
        } else {
            // 没有进程到达，时间前进到下一个进程到达时间
            int next_arrival = INT_MAX;
            for (int i = 0; i < scheduler->count; i++) {
                if (!scheduler->processes[i].completed && 
                    scheduler->processes[i].arrival_time < next_arrival) {
                    next_arrival = scheduler->processes[i].arrival_time;
                }
            }
            if (next_arrival != INT_MAX) {
                scheduler->current_time = next_arrival;
            }
        }
    }
}

// HRRN调度算法
void hrrn(Scheduler *scheduler) {
    scheduler->current_time = 0;
    int completed = 0;
    
    while (completed < scheduler->count) {
        // 计算所有已到达进程的响应比
        int selected_index = -1;
        float highest_response_ratio = -1;
        
        for (int i = 0; i < scheduler->count; i++) {
            Process *p = &scheduler->processes[i];
            if (!p->completed && p->arrival_time <= scheduler->current_time) {
                int waiting_time = scheduler->current_time - p->arrival_time;
                p->response_ratio = (float)(waiting_time + p->service_time) / p->service_time;
                
                if (p->response_ratio > highest_response_ratio) {
                    highest_response_ratio = p->response_ratio;
                    selected_index = i;
                }
            }
        }
        
        if (selected_index != -1) {
            Process *p = &scheduler->processes[selected_index];
            p->start_time = scheduler->current_time;
            p->waiting_time = scheduler->current_time - p->arrival_time;
            scheduler->current_time += p->service_time;
            p->finish_time = scheduler->current_time;
            p->completed = 1;
            completed++;
            
            add_to_gantt(scheduler, p->name, p->start_time, p->finish_time);
        } else {
            // 没有进程到达，时间前进到下一个进程到达时间
            int next_arrival = INT_MAX;
            for (int i = 0; i < scheduler->count; i++) {
                if (!scheduler->processes[i].completed && 
                    scheduler->processes[i].arrival_time < next_arrival) {
                    next_arrival = scheduler->processes[i].arrival_time;
                }
            }
            if (next_arrival != INT_MAX) {
                scheduler->current_time = next_arrival;
            }
        }
    }
}

// RR调度算法
void rr(Scheduler *scheduler, int time_quantum) {
    scheduler->current_time = 0;
    int completed = 0;
    
    // 重置所有进程的剩余时间
    for (int i = 0; i < scheduler->count; i++) {
        scheduler->processes[i].remaining_time = scheduler->processes[i].service_time;
    }
    
    while (completed < scheduler->count) {
        int executed = 0;
        
        for (int i = 0; i < scheduler->count; i++) {
            Process *p = &scheduler->processes[i];
            
            if (!p->completed && p->arrival_time <= scheduler->current_time && p->remaining_time > 0) {
                if (p->start_time == -1) {
                    p->start_time = scheduler->current_time;
                }
                
                int execution_time = (p->remaining_time < time_quantum) ? p->remaining_time : time_quantum;
                int start_execution = scheduler->current_time;
                
                scheduler->current_time += execution_time;
                p->remaining_time -= execution_time;
                
                add_to_gantt(scheduler, p->name, start_execution, scheduler->current_time);
                
                // 更新其他进程的等待时间
                for (int j = 0; j < scheduler->count; j++) {
                    if (j != i && !scheduler->processes[j].completed && 
                        scheduler->processes[j].arrival_time <= start_execution) {
                        scheduler->processes[j].waiting_time += execution_time;
                    }
                }
                
                if (p->remaining_time == 0) {
                    p->finish_time = scheduler->current_time;
                    p->completed = 1;
                    completed++;
                }
                
                executed = 1;
            }
        }
        
        if (!executed) {
            // 没有进程可执行，时间前进
            scheduler->current_time++;
        }
    }
}

// 优先级抢占式调度算法
void preemptive_priority(Scheduler *scheduler) {
    scheduler->current_time = 0;
    int completed = 0;
    int current_process = -1;
    
    // 重置所有进程的剩余时间
    for (int i = 0; i < scheduler->count; i++) {
        scheduler->processes[i].remaining_time = scheduler->processes[i].service_time;
    }
    
    while (completed < scheduler->count) {
        // 检查是否有更高优先级的进程到达
        int highest_priority_index = -1;
        int highest_priority = INT_MAX;
        
        for (int i = 0; i < scheduler->count; i++) {
            Process *p = &scheduler->processes[i];
            if (!p->completed && p->arrival_time <= scheduler->current_time && p->remaining_time > 0) {
                if (p->priority < highest_priority) {
                    highest_priority = p->priority;
                    highest_priority_index = i;
                }
            }
        }
        
        // 如果当前运行的进程需要被抢占
        if (current_process != -1 && highest_priority_index != current_process && 
            highest_priority < scheduler->processes[current_process].priority) {
            // 当前进程被抢占
            current_process = highest_priority_index;
        } else if (current_process == -1 && highest_priority_index != -1) {
            current_process = highest_priority_index;
        }
        
        if (current_process != -1) {
            Process *p = &scheduler->processes[current_process];
            
            if (p->start_time == -1) {
                p->start_time = scheduler->current_time;
            }
            
            int start_execution = scheduler->current_time;
            scheduler->current_time++;
            p->remaining_time--;
            
            add_to_gantt(scheduler, p->name, start_execution, scheduler->current_time);
            
            // 更新其他就绪进程的等待时间
            for (int i = 0; i < scheduler->count; i++) {
                if (i != current_process && !scheduler->processes[i].completed && 
                    scheduler->processes[i].arrival_time <= start_execution && 
                    scheduler->processes[i].remaining_time > 0) {
                    scheduler->processes[i].waiting_time++;
                }
            }
            
            if (p->remaining_time == 0) {
                p->finish_time = scheduler->current_time;
                p->completed = 1;
                completed++;
                current_process = -1;
            }
        } else {
            scheduler->current_time++;
        }
    }
}
