FROM python:3.10

COPY WORKDIR /app

COPY ./ requirements.txt

RUN pip install -r requirements.txt /app/

COPY ./app /code/app

EXPOSE 8000

CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8000"]