# Computer_Network_HW1

소켓 프로그래밍
# 1.	Hardcoded된 경우

## 핵심 소스코드
### Server 소스코드

<img width="195" alt="image" src="https://github.com/prgmr99/Computer_Network_HW1/assets/76275691/814c9528-618f-427a-b682-ce418e8b90ed">
<div>
  하드코딩된 포트번호이다.
</div>
<img width="437" alt="image" src="https://github.com/prgmr99/Computer_Network_HW1/assets/76275691/59a948d8-87dc-47cf-b456-b86e2a0e5f30">
<div>
  포트번호를 초기화시켜주었다.
</div>
 

### Client 소스코드

<img width="261" alt="image" src="https://github.com/prgmr99/Computer_Network_HW1/assets/76275691/c8ea737c-8aad-449e-b74e-9f619a38d48d">
<div>
  하드코딩된 IP주소와 포트번호이다.
</div>
<img width="432" alt="image" src="https://github.com/prgmr99/Computer_Network_HW1/assets/76275691/3a569916-85fd-4117-a327-86a74c69430f">
<div>
  하드코딩된 정보를 모두 초기화해주었다.
</div>
 

## 결과물
### Server 터미널
<img width="452" alt="image" src="https://github.com/prgmr99/Computer_Network_HW1/assets/76275691/c6508a8b-6073-4a6f-b050-c3aa5d832e00">


### Client 터미널
<img width="452" alt="image" src="https://github.com/prgmr99/Computer_Network_HW1/assets/76275691/2536be51-efe1-4580-adce-be16499db47d">






# 2.	Command line에서 입력을 받는 경우와 INADDR_ANY를 사용한 경우

## 핵심 소스코드
### Server 소스코드

<div>우선 Server 소스코드에서는 command line에서 port 번호만 입력하여 서버를 오픈한다.</div>
<img width="451" alt="image" src="https://github.com/prgmr99/Computer_Network_HW1/assets/76275691/77fe1441-f898-43e4-b0c3-cd2693e13661">


<div>
  위의 소스코드에 대해서 간단하게 설명을 하면 처음에 static struct sockaddr_in server_addr을 선언하여 서버의 주소 정보를 저장한다.

Memset을 이용하여 구조체를 모두 0으로 초기화한다.
두 번째 줄의 코드는 구조체의 주소 패밀리를 설정하는 코드이다. 
AF_INET은 IPv4 주소 패밀리를 나타낸다.
세 번째 줄의 코드는 서버의 IP주소를 설정한다. INADDR_ANY는 서버가 가능한 모든 네트워크 인터페이스로부터 연결을 수락할 수 있도록 하는 특수한 IP주소이다. 
마지막 줄의 코드는 서버의 포트 번호를 설정하는 코드이다.
argv[1]은 command line에서 입력받은 포트 번호이고 이를 정수로 변환하여 포트 번호로 설정한다.
</div>


### Client 소스코드

<img width="441" alt="image" src="https://github.com/prgmr99/Computer_Network_HW1/assets/76275691/2cce3080-527a-4533-a479-2f136709f245">

<div>
  Command line에서 입력받은 IP주소와 포트 번호를 클라이언트 주소 정보를 저장하기 위한 구조체에 저장한다.
Client_fd에는 클라이언트 소켓을 생성한 것을 저장한다.
‘client_addr.sin_addr.s_addr = inet_addr(IP)‘를 통해 클라이언트 주소 구조체 ‘client_addr’의 IP주소 필드를 서버의 IP주소로 설정한다.
</div>




## 결과물

### Server 터미널
<img width="452" alt="image" src="https://github.com/prgmr99/Computer_Network_HW1/assets/76275691/d72aa1a9-f368-4635-a4b8-aad812b22978">



### Client 터미널
<img width="452" alt="image" src="https://github.com/prgmr99/Computer_Network_HW1/assets/76275691/ee214dc5-5324-4700-830d-ddcd7b991afb">


