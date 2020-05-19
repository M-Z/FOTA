import { Component } from '@angular/core';

import { Chart } from 'chart.js';
import { HttpService } from 'app/core/services/HTTP/http.service';

interface downloadRequestStats { succeed: number, failed: number, unknown: number }

@Component({
  selector: 'app-stats',
  templateUrl: './stats.component.html',
  styleUrls: ['./stats.component.scss']
})
export class StatsComponent {
  public error: string;
  private barChart: Chart;
  private pieChart: Chart;

  constructor(
    private http: HttpService
  ) {
    this.error = 'No Statistics loaded.';
  }

  ngOnInit() {
    const downloadRequestChart = document.getElementById('downloadChart') as HTMLCanvasElement,
      versionRequestChart = document.getElementById('versionChart') as HTMLCanvasElement;

    // Comparison bar chart
    this.barChart = new Chart(versionRequestChart, {
      type: 'horizontalBar',
      data: {
        datasets: [{
          label: 'Version Requests',
          data: [
            0
          ],
          backgroundColor: [
            'rgba(0,242,242,0.5)'
          ]
        }, {
          label: 'Download Requests',
          data: [
            0
          ],
          backgroundColor: [
            'rgba(0,117,242, 0.5)',
          ]
        }],
        labels: ['Version vs. Download Requests']
      },
      options: {
        responsive: true,
        scales: {
          xAxes: [{
            gridLines: {
              display: true
            }, ticks: {
              beginAtZero: true,
              callback: function(value: number) { if (Number.isInteger(value)) { return value; } },
              stepSize: 1,
              minor: {
                fontColor: 'white'
              }
            }
          }],
          yAxes: [{
            gridLines: {
              display: false
            },
            ticks: {
              display: false
            }
          }]
        },
        legend: {
          labels: {
            fontColor: 'white'
          }
        }
      }
    });

    // Pie chart
    this.pieChart = new Chart(downloadRequestChart, {
      type: 'doughnut',
      data: {
        datasets: [{
          label: 'Download Statistics',
          data: [
            0, 0, 0
          ],
          backgroundColor: [
            'rgba(156,252,151,0.5)',
            'rgba(254,74,73, 0.5)',
            'rgba(25,25,25,0.5)'
          ]
        }],
        labels: ['Succeed', 'Failed', 'Error']
      },
      options: {
        responsive: true,
        title: {
          display: true,
          fontColor: 'white',
          text: 'Downlaod Statistics'
        },
        legend: {
          labels: {
            fontColor: 'white'
          }
        },
        elements: {
          arc: {
            borderColor: 'rgba(255,255,255, 0.5)'
          }
        }
      }
    });
  }

  loadChart(firmware: { data: { _id: string } }) {

    this.http.invoke({
      method: 'get',
      path: 'statistics/' + firmware.data._id,
    }).subscribe({
      next: (chartData: { downloadRequest: downloadRequestStats, versionRequest: number }) => {
        this.error = null;

        this.barChart.data.datasets[0].data[0] = chartData.versionRequest || 0;
        this.barChart.data.datasets[1].data[0] = chartData.downloadRequest.succeed || 0 + chartData.downloadRequest.failed || 0 + chartData.downloadRequest.unknown || 0;
        this.barChart.update();

        this.pieChart.data.datasets[0].data[0] = chartData.downloadRequest.succeed || 0;
        this.pieChart.data.datasets[0].data[1] = chartData.downloadRequest.failed || 0;
        this.pieChart.data.datasets[0].data[2] = chartData.downloadRequest.unknown || 0;
        this.pieChart.update();
      },
      error: () => this.error = 'No Statistics Found for this firmware.'
    });

  }

}
