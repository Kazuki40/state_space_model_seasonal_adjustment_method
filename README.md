This program estimate parameter with the linear regression model.
It's a simplified seasonal adjustment model.
This data-set is COVID-19 with the number of infected persons between 4/1/2020 to 3/31/2022 (2 years) in Japan.

How to 
input/ .csv
　stuffing and recording form above.
  
model 
 this program has the linear and Gaussian state-space models.
 This program can extend it to the non-linear and non-Gaussian state-space model and the self-organisation sate-space model. But, time-varying models are not supported.
 If you want to estimate it, you make separate data loaded, and you must define a design matrix.
 Hyperparameter optimisation is also not supported.
 
 
 system model(1)
 (■8(𝑎@𝑏@𝑤_𝑡1@𝑤_𝑡2@𝑤_𝑡3@𝑤_𝑡4@𝑤_𝑡5@𝑤_𝑡6))_𝑡=(■8(1&0&0&0&0&0&0&0@1&1&0&0&0&0&0&0@0&0&−1&−1&−1&−1&−1&−1@0&0&1&0&0&0&0&0@0&0&0&1&0&0&0&0@0&0&0&0&1&0&0&0@0&0&0&0&0&1&0&0@0&0&0&0&0&0&1&0))(■8(𝑎@𝑏@𝑤_𝑡1@𝑤_𝑡2@𝑤_𝑡3@𝑤_𝑡4@𝑤_𝑡5@𝑤_𝑡6))_(𝑡−1)+(■8(1@1@1@0@0@0@0@0))𝜀
![image](https://user-images.githubusercontent.com/54506893/170943084-60dee2a9-9cd3-4388-927f-2b2495e80e73.png)

observation model(2)
𝑦_𝑡=(■8(0&1&1&0&0&0&0&0)) (■8(𝑎@𝑏@𝑤_𝑡1@𝑤_𝑡2@𝑤_𝑡3@𝑤_𝑡4@𝑤_𝑡5@𝑤_𝑡6))_𝑡+𝛾
![image](https://user-images.githubusercontent.com/54506893/170943261-4deca783-ca24-4e7b-ac1c-823ffb5f22a4.png)

when caluctate observation model, use to observation likelihood model (3)
𝛾=1/√(2𝜋𝜎^2 ) 𝑒^((−(𝑦−𝐻𝑥)^2/(2𝜎^2 )) )![image](https://user-images.githubusercontent.com/54506893/170944159-75aa30a8-0065-4782-af7c-18b67e0f1d35.png)

inital distribution
𝑝(𝑥_0 )=𝑁(〖0,10〗^8 )![image](https://user-images.githubusercontent.com/54506893/170944358-d1e641bf-8bfd-442c-89f6-bd540ffe1d42.png)

it is meanuninformed prior distribution

This program operates at C++11 or above.
this project is an issue.

